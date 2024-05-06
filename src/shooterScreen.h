#include "gameCommon.h"

#ifndef SHOOTER_SCREEN_H
#define SHOOTER_SCREEN_H

#define PLAYER_HEIGHT 2.0
#define MOUSE_SPEED 0.01
#define PLAYER_SPEED 10.0

typedef struct ShooterPlayer {
    Camera3D camera;

    Vector3 position;
    Vector3 direction;
    Vector3 velocity;

    Vector2 cameraAngle;
} ShooterPlayer;

typedef struct ShooterScreen {
    ShooterPlayer player;
} ShooterScreen;

void initShooterScreeen(ShooterScreen* shooterScreen, Game* game);
void updateShooterScreen(ShooterScreen* shooterScreen, Game* game);
void closeShooterScreen(ShooterScreen* shooterScreen);

void enterShooterScreen(Game* game);
void leaveShooterScreen(Game* game);

#endif
