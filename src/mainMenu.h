#include "gameCommon.h"
#include "animation.h"
#include "ui.h"
#include "clicky.h"

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

typedef struct MainMenu {
    Animation startButtonAnimation;
    TexturedButton startButton;
} MainMenu;

void initMainMenu(MainMenu* mainMenu, Game* game);
void updateMainMenu(MainMenu* mainMenu, Game* game);
void closeMainMenu(MainMenu* mainMenu);

#endif
