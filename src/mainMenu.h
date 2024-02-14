#include "gameCommon.h"

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

typedef struct MainMenu {
} MainMenu;

void initMainMenu(MainMenu* mainMenu, Game* game);
void updateMainMenu(MainMenu* mainMenu, Game* game);
void closeMainMenu(MainMenu* mainMenu);

#endif
