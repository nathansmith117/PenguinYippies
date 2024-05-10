#include "gameCommon.h"
#include "animation.h"
#include "ui.h"
#include "clicky.h"
#include "shop.h"

#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#define RUN_SHOOTER_GAME_COUNT_START 500

typedef enum GamePlayPlace {
    CLICKY_DESKTOP_PLACE,
    SHOP_PLACE
} GamePlayPlace;

typedef enum ToolId {
    CLICKER_TOOL,
    BOOPER_TOOL
} ToolId;

#define TOOL_COUNT 2

typedef struct GameScreen {
    GamePlayPlace place;

    TexturedButton toGameButton;
    TexturedButton toEmperorsEmporiumButton;

    Shop shop;

    ToolId tool;

    int nextShootingStoneCount;
} GameScreen;

void initGameScreen(GameScreen* gameScreen, Game* game);
void updateGameScreen(GameScreen* gameScreen, Game* game);
void closeGameScreen(GameScreen* gameScreen);

void setGameScreenTool(GameScreen* gameScreen, ToolId tool);

#endif
