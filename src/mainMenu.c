#include "mainMenu.h"
#include "game.h"
#include "assets.h"

void initMainMenu(MainMenu* mainMenu, Game* game)
{
    // Start button stuff.
    mainMenu->startButtonAnimation = createAnimation(
        &game->assets.animations[BUTTON_BOX_ANIMATION],
        ANIMATION_DEFAULT_DELAY
    );

    playAnimation(&mainMenu->startButtonAnimation);

    Texture* startButtonTexture = &mainMenu->startButtonAnimation.texture;

    int width = GetScreenWidth();
    int height = GetScreenHeight();

    mainMenu->startButton = createTexturedButton(
        startButtonTexture,
        (Rectangle){
            width / 2.0 - startButtonTexture->width / 2.0,
            height / 2.0 - startButtonTexture->height,
            startButtonTexture->width,
            startButtonTexture->height
        },
        "Start",
        WHITE,
        BLACK
    );

    mainMenu->startButton.fontSize = 50;
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

    // Draw start button.
    runAnimation(&mainMenu->startButtonAnimation);
    bool startPressed = updateTexturedButton(&mainMenu->startButton);

    if (startPressed)
    {
        game->currentScreen = GAME_SCREEN;
    }
}

void closeMainMenu(MainMenu* mainMenu)
{
    closeAnimation(&mainMenu->startButtonAnimation);
}
