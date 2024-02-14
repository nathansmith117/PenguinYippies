#include "gameCommon.h"
#include "mainMenu.h"
#include "gameScreen.h"

#ifndef GAME_H
#define GAME_H

typedef enum ScreenId {
    MAIN_MENU_SCREEN,
    GAME_SCREEN
} ScreenId;

typedef struct Game {
    ScreenId currentScreen;
    MainMenu mainMenu;
    GameScreen gameScreen;
} Game;

void initGame(Game* game);
void updateGame(Game* game);
void closeGame(Game* game);

#endif
