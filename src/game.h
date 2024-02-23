#include "gameCommon.h"
#include "mainMenu.h"
#include "gameScreen.h"
#include "assets.h"
#include "clicky.h"

#ifndef GAME_H
#define GAME_H

typedef enum ScreenId {
    MAIN_MENU_SCREEN,
    GAME_SCREEN
} ScreenId;

typedef struct Game {
    Assets assets;

    // Screens.
    ScreenId currentScreen;
    MainMenu mainMenu;
    GameScreen gameScreen;

    Clickies clickies;

    // Wacky little render texture to make it look more like a unity game lmao.
    RenderTexture screenTexture;
} Game;

void initGame(Game* game);
void updateGame(Game* game);
void closeGame(Game* game);

#endif
