#include "shooterScreen.h"
#include "game.h"
#include "assets.h"
#include <raylib.h>
#include <raymath.h>

void initShooterScreeen(ShooterScreen* shooterScreen, Game* game)
{
    // Setup player.
    shooterScreen->player = (ShooterPlayer){
        .camera = (Camera3D){
            .up = (Vector3){0.0, 1.0, 0.0},
            .fovy = 90.0,
            .projection = CAMERA_PERSPECTIVE
        },
        .position = (Vector3){0.0, PLAYER_HEIGHT, 0.0},
        .direction = (Vector3){0.0, 0.0, 1.0},
        .velocity = Vector3Zero(),
        .cameraAngle = Vector2Zero(),
        .jumpStage = 0
    };

    shooterScreen->bestPNPS = 0.0;

    resetShooterScreen(shooterScreen);
}

void shootBulletShooterScreen(ShooterScreen* shooterScreen, Game* game)
{
    ShooterPlayer* player = &shooterScreen->player;

    // Bullet ray.
    Ray ray = (Ray){
        .position = player->position,
        .direction = player->direction
    };

    // Bounding box that will be used for all penguins.
    BoundingBox penguinBox = (BoundingBox){
        .min = (Vector3){-0.5, -1.0, -0.5},
        .max = (Vector3){0.5, 1.0, 0.5}
    };

    ShooterPenguin* closestPenguin = NULL;
    float closestDistance = 0.0;

    for (int i = 0; i < SHOOTER_PENGUIN_COUNT; ++i)
    {
        ShooterPenguin* penguin = &shooterScreen->penguins[i];

        if (penguin->isDead)
        {
            continue;
        }

        // Get the box at the penguins position.
        BoundingBox currentBox = (BoundingBox){
            .min = Vector3Add(penguin->position, penguinBox.min),
            .max = Vector3Add(penguin->position, penguinBox.max)
        };

        // Check collision.
        if (GetRayCollisionBox(ray, currentBox).hit)
        {
            float distance = Vector3Distance(penguin->position, shooterScreen->player.position);

            // Is closest or first.
            if (distance < closestDistance || closestPenguin == NULL)
            {
                closestPenguin = penguin;
                closestDistance = distance;
            }
        }
    }

    // Removed penguin if shot.
    if (closestPenguin != NULL)
    {
        closestPenguin->isDead = true;
        ++shooterScreen->killCount;
    }
}

void updateShooterScreenControls(ShooterScreen* shooterScreen, Game* game)
{
    ShooterPlayer* player = &shooterScreen->player;
    Vector2 mouseDelta = Vector2Scale(GetMouseDelta(), MOUSE_SPEED);

    // Update camera angle.
    player->cameraAngle = Vector2Add(player->cameraAngle, mouseDelta);
    player->cameraAngle.x = Wrap(player->cameraAngle.x, -PI, PI);
    player->cameraAngle.y = Clamp(player->cameraAngle.y, -PI / 2.5, PI / 2.5);

    // Set direction.
    Matrix matrix = MatrixRotateXYZ((Vector3){-player->cameraAngle.y, player->cameraAngle.x, 0.0});
    player->direction = (Vector3){matrix.m2, matrix.m6, matrix.m10};

    // Update velocity.
    player->velocity = Vector3Zero();

    if (IsKeyDown(KEY_W))
    {
        player->velocity.z += cos(player->cameraAngle.x);
        player->velocity.x += -sin(player->cameraAngle.x);
    }
    if (IsKeyDown(KEY_A))
    {
        player->velocity.z += cos(player->cameraAngle.x - (PI / 2.0));
        player->velocity.x += -sin(player->cameraAngle.x - (PI / 2.0));
    }
    if (IsKeyDown(KEY_S))
    {
        player->velocity.z += -cos(player->cameraAngle.x);
        player->velocity.x += sin(player->cameraAngle.x);
    }
    if (IsKeyDown(KEY_D))
    {
        player->velocity.z += cos(player->cameraAngle.x + (PI / 2.0));
        player->velocity.x += -sin(player->cameraAngle.x + (PI / 2.0));
    }

    // Shoot
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        shootBulletShooterScreen(shooterScreen, game);
    }

    player->velocity = Vector3Scale(player->velocity, PLAYER_SPEED);
}

void updateShooterScreenPenguins(ShooterScreen* shooterScreen, Game* game)
{
    double currentTime = GetTime();
    double frameTime = GetFrameTime();
    Texture texture = game->assets.textures[PENGUIN_BILLBOARD_TEXTURE];
    ShooterPenguin* penguins = shooterScreen->penguins;

    for (int i = 0; i < SHOOTER_PENGUIN_COUNT; ++i)
    {
        // It is dead ):
        if (penguins[i].isDead)
        {
            continue;
        }
        
        // Change velocity.
        if (FloatEquals(penguins[i].changeSpeedDelay, 0.0)) // Goes at you.
        {
            penguins[i].velocity = Vector3Subtract(shooterScreen->player.position, penguins[i].position);
            penguins[i].velocity = Vector3Scale(Vector3Normalize(penguins[i].velocity), SHOOTER_PENGUIN_SPEED);
            penguins[i].velocity.y = 0.0;
        }
        else if (currentTime - penguins[i].lastVelocityChange >= penguins[i].changeSpeedDelay)
        {
            if (Vector3Length(penguins[i].position) >= SHOOTER_MAP_SIZE) // Too far away.
            {
                // Make it come closer.
                penguins[i].velocity = Vector3Negate(penguins[i].position);
                penguins[i].velocity.y = 0.0;
                penguins[i].velocity = Vector3Scale(Vector3Normalize(penguins[i].velocity), SHOOTER_PENGUIN_SPEED);
            }
            else
            {
                // Get random velocity.
                SetRandomSeed(time(NULL));

                penguins[i].velocity = (Vector3){
                    (float)GetRandomValue(-1000, 1000) / 1000.0,
                    0.0,
                    (float)GetRandomValue(-1000, 1000) / 1000.0
                };

                penguins[i].velocity = Vector3Scale(Vector3Normalize(penguins[i].velocity), SHOOTER_PENGUIN_SPEED);
            }

            penguins[i].lastVelocityChange = currentTime;
        }

        // Apply velocity.
        penguins[i].position = Vector3Add(
            penguins[i].position,
            Vector3Scale(penguins[i].velocity, frameTime)
        );

        // Draw them.
        DrawBillboard(shooterScreen->player.camera, texture, penguins[i].position, 2.0, WHITE);
    }
}

void drawCrosshairShooterScreen(int size, int thickness)
{
    int halfWidth = WINDOW_WIDTH / 2;
    int halfHeight = WINDOW_HEIGHT / 2;

    // Left to right.
    DrawLineEx((Vector2){halfWidth - size, halfHeight},
        (Vector2){halfWidth + size, halfHeight}, thickness, BLACK);

    // Top to bottom.
    DrawLineEx((Vector2){halfWidth, halfHeight - size},
        (Vector2){halfWidth, halfHeight + size}, thickness, BLACK);
}

void drawUIShooterScreen(ShooterScreen* shooterScreen, Game* game)
{
    drawCrosshairShooterScreen(10, 2);

    size_t bufSize = 256;
    char buf[bufSize];

    snprintf(buf, bufSize, "They are sleeping not dead (:\nTime playing: %d\nPenguins still awake: %d\n\n-w, a, s, d to move around\n-mouse to aim\n-and click to put a penguin to sleep",
        (int)(GetTime() - shooterScreen->startTime),
        SHOOTER_PENGUIN_COUNT - shooterScreen->killCount);

    DrawText(buf, 0, 0, 20, BLACK);
}

void drawShooterScreenEndLevel(ShooterScreen* shooterScreen, Game* game)
{
    // Set pnps.
    if (FloatEquals(shooterScreen->pnps, 0.0))
    {
        shooterScreen->pnps = (float)SHOOTER_PENGUIN_COUNT / (GetTime() - shooterScreen->startTime);

        // Find best pnps.
        if (shooterScreen->pnps > shooterScreen->bestPNPS)
        {
            shooterScreen->bestPNPS = shooterScreen->pnps;
        }
    }

    // Format message.
    size_t bufSize = 100;
    char buf[bufSize];

    snprintf(buf, bufSize, "Level done with a penguin naps per seconds (pnps) of: %f\n\tBest npns this game: %f",
        shooterScreen->pnps, shooterScreen->bestPNPS);

    // Draw it.
    DrawText(buf, WINDOW_WIDTH / 4.0, WINDOW_HEIGHT / 2.0, 25, BLACK);
}

void updateShooterScreen(ShooterScreen* shooterScreen, Game* game)
{
    ShooterPlayer* player = &shooterScreen->player;
    ClearBackground(PINK);

    updateShooterScreenControls(shooterScreen, game);

    // Apply velocity.
    player->position = Vector3Add(
        player->position,
        Vector3Scale(player->velocity, GetFrameTime())
    );

    // Camera things.
    player->camera.position = player->position;
    player->camera.target = Vector3Add(player->position, player->direction);

    // Draw 3d scene.
    BeginMode3D(shooterScreen->player.camera);

    DrawGrid(SHOOTER_MAP_SIZE, 2.0);
    updateShooterScreenPenguins(shooterScreen, game);

    EndMode3D();

    drawUIShooterScreen(shooterScreen, game);

    // End of level.
    if (shooterScreen->killCount == SHOOTER_PENGUIN_COUNT)
    {
        // Start timer.
        if (!shooterScreen->atEndLevel)
        {
            shooterScreen->endLevelStartTime = GetTime();
            shooterScreen->atEndLevel = true;
        }

        // Back to main game.
        if (GetTime() - shooterScreen->endLevelStartTime >= SHOOTER_END_LEVEL_TIME || IsKeyPressed(KEY_SPACE))
        {
            leaveShooterScreen(game);
            game->currentScreen = GAME_SCREEN;
        }
        
        drawShooterScreenEndLevel(shooterScreen, game);
    }
}

void closeShooterScreen(ShooterScreen* shooterScreen)
{
}

void resetShooterScreen(ShooterScreen* shooterScreen)
{
    // Player.
    ShooterPlayer* player = &shooterScreen->player;
    player->position = (Vector3){0.0, PLAYER_HEIGHT, 0.0};
    player->direction = (Vector3){0.0, 0.0, 1.0};
    player->cameraAngle = Vector2Zero();
    player->jumpStage = 0;
    player->velocity = Vector3Zero();

    // Penguins.
    SetRandomSeed(time(NULL));

    for (int i = 0; i < SHOOTER_PENGUIN_COUNT; ++i)
    {
        Vector3 randomPosition = (Vector3){
            GetRandomValue(-SHOOTER_MAP_SIZE, SHOOTER_MAP_SIZE),
            SHOOTER_PENGUIN_HEIGHT,
            GetRandomValue(-SHOOTER_MAP_SIZE, SHOOTER_MAP_SIZE)
        };

        shooterScreen->penguins[i].position = randomPosition;
        shooterScreen->penguins[i].velocity = Vector3Zero();
        shooterScreen->penguins[i].changeSpeedDelay = GetRandomValue(SHOOTER_PENGUIN_CHANGE_DELAY_MIN,
                                                                     SHOOTER_PENGUIN_CHANGE_DELAY_MAX);
        shooterScreen->penguins[i].lastVelocityChange = 0.0;
        shooterScreen->penguins[i].isDead = false;
    }

    shooterScreen->pnps = 0.0;
    shooterScreen->killCount = 0;

    // Time.
    shooterScreen->startTime = GetTime();

    shooterScreen->atEndLevel = false;
}

void enterShooterScreen(Game* game)
{
    game->currentScreen = SHOOTER_SCREEN;
    DisableCursor();
    resetShooterScreen(&game->shooterScreen);
}
void leaveShooterScreen(Game* game)
{
    EnableCursor();
}
