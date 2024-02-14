#include "gameCommon.h"

#ifndef GAME_H
#define GAME_H

typedef enum ScreenId
{
    MAIN_MENU_SCREEN,
    GAME_SCREEN
} ScreenId;

typedef struct Game
{
} Game;

void initGame(Game* game);
void updateGame(Game* game);
void closeGame(Game* game);

#endif
