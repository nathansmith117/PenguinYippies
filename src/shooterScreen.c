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
        .cameraAngle = Vector2Zero()
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

    player->velocity = Vector3Scale(player->velocity, PLAYER_SPEED);
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
