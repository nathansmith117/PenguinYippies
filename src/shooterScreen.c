#include "shooterScreen.h"
#include "game.h"
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

    DrawGrid(32, 2.0);

    EndMode3D();
}

void closeShooterScreen(ShooterScreen* shooterScreen)
{
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
