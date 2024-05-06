#include "gameCommon.h"

#ifndef SHOOTER_SCREEN_H
#define SHOOTER_SCREEN_H

#define SHOOTER_MAP_SIZE 64

#define PLAYER_HEIGHT 2.0
#define PLAYER_SPEED 10.0
#define PLAYER_JUMP_SPEED 15.0
#define PLAYER_FALL_SPEED 18.0
#define PLAYER_JUMP_HEIGHT 8.0

#define MOUSE_SPEED 0.01

#define SHOOTER_PENGUIN_COUNT 5
#define SHOOTER_PENGUIN_HEIGHT 2.0

typedef struct ShooterPlayer {
    Camera3D camera;

    Vector3 position;
    Vector3 direction;
    Vector3 velocity;

    Vector2 cameraAngle;

    int jumpStage;
    float sleepyness;
} ShooterPlayer;

// Penguin to "put to sleep".
typedef struct ShooterPenguin {
    Vector3 position;
    Vector3 velocity;
    float sleepyness;
} ShooterPenguin;

typedef struct ShooterScreen {
    ShooterPlayer player;
    ShooterPenguin penguins[SHOOTER_PENGUIN_COUNT];
} ShooterScreen;

void initShooterScreeen(ShooterScreen* shooterScreen, Game* game);
void updateShooterScreen(ShooterScreen* shooterScreen, Game* game);
void closeShooterScreen(ShooterScreen* shooterScreen);

void resetShooterScreen(ShooterScreen* shooterScreen);

void enterShooterScreen(Game* game);
void leaveShooterScreen(Game* game);

#endif
