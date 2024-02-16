#include "gameCommon.h"
#include "animation.h"

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

typedef struct MainMenu {
    Animation startButtonAnimation;
} MainMenu;

void initMainMenu(MainMenu* mainMenu, Game* game);
void updateMainMenu(MainMenu* mainMenu, Game* game);
void closeMainMenu(MainMenu* mainMenu);

#endif
