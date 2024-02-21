#include "gameScreen.h"
#include "game.h"

void initGameScreen(GameScreen* gameScreen, Game* game)
{
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    int navigationButtonSize = 100;
    int navigationButtonX = width - navigationButtonSize - 5.0;

    // Navigation buttons.
    gameScreen->toGameButton = createTexturedButton(
        &game->assets.textures[TO_GAME_ICON_TEXTURE],
        (Rectangle){navigationButtonX, 5.0, navigationButtonSize, navigationButtonSize},
        "",
        WHITE,
        BLACK
    );

    gameScreen->toEmperorsEmporiumButton = createTexturedButton(
        &game->assets.textures[TO_EMPERORS_EMPORIUM_ICON_TEXTURE],
        (Rectangle){navigationButtonX, navigationButtonSize + 15.0, navigationButtonSize, navigationButtonSize},
        "",
        WHITE,
        BLACK
    );
}

void updateGameScreen(GameScreen* gameScreen, Game* game)
{
     // Draw background.
    Texture background = game->assets.textures[MAIN_SCREEN_BACKGROUND_TEXTURE];

    DrawTexturePro(
        background,
        (Rectangle){0.0, 0.0, background.width, background.height},
        (Rectangle){0.0, 0.0, GetScreenWidth(), GetScreenHeight()},
        (Vector2){0.0, 0.0},
        0.0,
        WHITE
    );

    // Navigation buttons.
    updateTexturedButton(&gameScreen->toGameButton);
    updateTexturedButton(&gameScreen->toEmperorsEmporiumButton);
}

void closeGameScreen(GameScreen* gameScreen)
{
}

