#include "mainMenu.h"
#include "game.h"
#include "assets.h"

void initMainMenu(MainMenu* mainMenu, Game* game)
{
    mainMenu->startButtonAnimation = createAnimation(
        &game->assets.animations[BUTTON_BOX_ANIMATION],
        ANIMATION_DEFAULT_DELAY
    );
}

void updateMainMenu(MainMenu* mainMenu, Game* game)
{
    // Draw background.
    Texture background = game->assets.textures[PENGUIN_BACKGROUND_TEXTURE];

    DrawTexturePro(
        background,
        (Rectangle){0.0, 0.0, background.width, background.height},
        (Rectangle){0.0, 0.0, GetScreenWidth(), GetScreenHeight()},
        (Vector2){0.0, 0.0},
        0.0,
        WHITE
    );
}

void closeMainMenu(MainMenu* mainMenu)
{
    closeAnimation(&mainMenu->startButtonAnimation);
}
