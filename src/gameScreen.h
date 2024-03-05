#include "gameCommon.h"
#include "animation.h"
#include "ui.h"
#include "clicky.h"

#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

typedef enum GamePlayPlace {
    CLICKY_DESKTOP_PLACE,
    SHOP_PLACE
} GamePlayPlace;

typedef struct GameScreen {
    GamePlayPlace place;

    TexturedButton toGameButton;
    TexturedButton toEmperorsEmporiumButton;

    // The little button panel at the bottom.
    Animation buttonPanelSharedAnimation;
    TexturedButton upgradesButton;
    TexturedButton achievementsButton;
    TexturedButton rebirthButton;
    TexturedButton statisticsButton;
} GameScreen;

void initGameScreen(GameScreen* gameScreen, Game* game);
void updateGameScreen(GameScreen* gameScreen, Game* game);
void closeGameScreen(GameScreen* gameScreen);

#endif
