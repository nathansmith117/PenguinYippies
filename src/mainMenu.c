#include "mainMenu.h"
#include "game.h"
#include "assets.h"
#include <raylib.h>

void initMainMenu(MainMenu* mainMenu, Game* game)
{
    mainMenu->startButtonAnimation = createAnimation(
        &game->assets.animations[BUTTON_BOX_ANIMATION],
        ANIMATION_DEFAULT_DELAY
    );
}

void updateMainMenu(MainMenu* mainMenu, Game* game)
{
    ClearBackground(RAYWHITE);

    DrawTextureEx(mainMenu->startButtonAnimation.texture, (Vector2){100.0, 100.0}, 0.0, 1.0, WHITE);
    runAnimation(&mainMenu->startButtonAnimation);

    DrawFPS(0, 0);
}

void closeMainMenu(MainMenu* mainMenu)
{
    closeAnimation(&mainMenu->startButtonAnimation);
}
