#include "mainMenu.h"
#include "game.h"
#include "assets.h"

void initMainMenu(MainMenu* mainMenu, Game* game)
{
    mainMenu->startButtonAnimation = createAnimation(
        &game->assets.animations[PENGUIN_LOL_ANIMATION],
        ANIMATION_DEFAULT_DELAY
    );
}

void updateMainMenu(MainMenu* mainMenu, Game* game)
{
    ClearBackground(RAYWHITE);

    DrawTextureEx(mainMenu->startButtonAnimation.texture, (Vector2){100.0, 100.0}, 0.0, 0.1, WHITE);
    runAnimation(&mainMenu->startButtonAnimation);

    if (IsKeyPressed(KEY_SPACE))
    {
        toggleAnimation(&mainMenu->startButtonAnimation);
    }

    DrawFPS(0, 0);
}

void closeMainMenu(MainMenu* mainMenu)
{
    closeAnimation(&mainMenu->startButtonAnimation);
}
