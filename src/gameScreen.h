#include "gameCommon.h"
#include "animation.h"
#include "ui.h"

#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

typedef struct GameScreen {
    TexturedButton toGameButton;
    TexturedButton toEmperorsEmporiumButton;

    // The little button panel at the bottem.
    Animation updateButtonAnimation;
    TexturedButton updateButton;

    Animation achievementsButtonAnimation;
    TexturedButton achievementsButton;

    Animation rebirthButtonAnimation;
    TexturedButton rebirthButton;

    Animation statisticsButtonAnimation;
    TexturedButton statisticsButton;
} GameScreen;

void initGameScreen(GameScreen* gameScreen, Game* game);
void updateGameScreen(GameScreen* gameScreen, Game* game);
void closeGameScreen(GameScreen* gameScreen);

#endif
