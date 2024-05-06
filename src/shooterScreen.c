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
        .jumpStage = 0,
        .sleepyness = 0.0
    };

    resetShooterScreen(shooterScreen);
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

    // Jump
    if (IsKeyPressed(KEY_SPACE))
    {
        player->jumpStage = 1;
    }

    player->velocity = Vector3Scale(player->velocity, PLAYER_SPEED);
}

void updateShooterScreenJump(ShooterScreen* shooterScreen, Game* game)
{
    ShooterPlayer* player = &shooterScreen->player;

    switch (player->jumpStage)
    {
        case 0: // No Jumpy
            break;
        case 1: // Jump up
            player->velocity.y = PLAYER_JUMP_SPEED;

            if (player->position.y >= PLAYER_JUMP_HEIGHT + PLAYER_HEIGHT)
            {
                player->jumpStage = 2;
            }

            break;
        case 2: // Fall
            player->velocity.y = -PLAYER_FALL_SPEED;

            if (player->position.y <= PLAYER_HEIGHT)
            {
                player->jumpStage = 0;
                player->position.y = PLAYER_HEIGHT;
            }

            break;
        default:
            break;
    }
}

void updateShooterScreenPenguins(ShooterScreen* shooterScreen, Game* game)
{
    Texture texture = game->assets.textures[PENGUIN_BILLBOARD_TEXTURE];
    ShooterPenguin* penguins = shooterScreen->penguins;

    for (int i = 0; i < SHOOTER_PENGUIN_COUNT; ++i)
    {
        DrawBillboard(shooterScreen->player.camera, texture, penguins[i].position, 2.0, WHITE);
    }
}

void updateShooterScreen(ShooterScreen* shooterScreen, Game* game)
{
    ShooterPlayer* player = &shooterScreen->player;
    ClearBackground(PINK);

    updateShooterScreenControls(shooterScreen, game);
    updateShooterScreenJump(shooterScreen, game);

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
    player->sleepyness = 0.0;
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
        shooterScreen->penguins[i].sleepyness = 0.0;
    }
}

void enterShooterScreen(Game* game)
{
    game->currentScreen = SHOOTER_SCREEN;
    DisableCursor();
}
void leaveShooterScreen(Game* game)
{
    EnableCursor();
}
