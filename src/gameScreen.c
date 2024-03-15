#include "gameScreen.h"
#include "game.h"
#include "assets.h"
#include <raylib.h>

void initGameScreen(GameScreen* gameScreen, Game* game)
{
    gameScreen->place = CLICKY_DESKTOP_PLACE;

    Assets* assets = &game->assets;
    int width = WINDOW_WIDTH;
    int height = WINDOW_HEIGHT;
    int navigationButtonSize = 100;
    int navigationButtonX = width - navigationButtonSize - 5.0;

    // Navigation buttons.
    gameScreen->toGameButton = createTexturedButton(
        &assets->textures[TO_GAME_ICON_TEXTURE],
        (Rectangle){navigationButtonX, 5.0, navigationButtonSize, navigationButtonSize},
        "",
        WHITE,
        BLACK
    );

    gameScreen->toEmperorsEmporiumButton = createTexturedButton(
        &assets->textures[TO_EMPERORS_EMPORIUM_ICON_TEXTURE],
        (Rectangle){navigationButtonX, navigationButtonSize + 15.0, navigationButtonSize, navigationButtonSize},
        "",
        WHITE,
        BLACK
    );

    // Button pannel thingy.
    gameScreen->buttonPanelSharedAnimation = createAnimation(&assets->animations[BUTTON_BOX_ANIMATION], ANIMATION_DEFAULT_DELAY);
    playAnimation(&gameScreen->buttonPanelSharedAnimation);

    Texture* buttonTexture = &gameScreen->buttonPanelSharedAnimation.texture;
    int buttonWidth = width / 4;
    int buttonHeight = buttonWidth / 2;
    int buttonY = height - buttonHeight;

    gameScreen->upgradesButton = createTexturedButton(
        buttonTexture,
        (Rectangle){0.0, buttonY, buttonWidth, buttonHeight},
        "Upgrades",
        WHITE,
        BLACK
    );

    gameScreen->achievementsButton = createTexturedButton(
        buttonTexture,
        (Rectangle){buttonWidth, buttonY, buttonWidth, buttonHeight},
        "Achievements",
        WHITE,
        BLACK
    );

    gameScreen->rebirthButton = createTexturedButton(
        buttonTexture,
        (Rectangle){buttonWidth * 2.0, buttonY, buttonWidth, buttonHeight},
        "Rebirth",
        WHITE,
        BLACK
    );

    gameScreen->statisticsButton = createTexturedButton(
        buttonTexture,
        (Rectangle){buttonWidth * 3.0, buttonY, buttonWidth, buttonHeight},
        "Statistics",
        WHITE,
        BLACK
    );

    initShop(&gameScreen->shop, game);
}

void updateGameScreenButtonPanel(GameScreen* gameScreen, Game* game)
{
    // Button panel.
    runAnimation(&gameScreen->buttonPanelSharedAnimation);
    updateTexturedButton(&gameScreen->upgradesButton);
    updateTexturedButton(&gameScreen->achievementsButton);
    updateTexturedButton(&gameScreen->rebirthButton);
    updateTexturedButton(&gameScreen->statisticsButton);
}

void updateGameScreenClickyDesktop(GameScreen* gameScreen, Game* game)
{
    updateGameScreenButtonPanel(gameScreen, game);

    // Clickies clickies.
    updateClickies(game, &game->clickies);
}

void updateGameScreen(GameScreen* gameScreen, Game* game)
{
     // Draw background.
    Texture background = game->assets.textures[MAIN_SCREEN_BACKGROUND_TEXTURE];

    DrawTexturePro(
        background,
        (Rectangle){0.0, 0.0, background.width, background.height},
        (Rectangle){0.0, 0.0, WINDOW_WIDTH, WINDOW_HEIGHT},
        (Vector2){0.0, 0.0},
        0.0,
        WHITE
    );

    // Navigation buttons.
    if (updateTexturedButton(&gameScreen->toGameButton))
    {
        gameScreen->place = CLICKY_DESKTOP_PLACE;
    }
    if (updateTexturedButton(&gameScreen->toEmperorsEmporiumButton))
    {
        gameScreen->place = SHOP_PLACE;
    }

    // assssssss hehehe
    switch (gameScreen->place)
    {
        case CLICKY_DESKTOP_PLACE:
            updateGameScreenClickyDesktop(gameScreen, game);
            break;
        case SHOP_PLACE:
            updateShop(&gameScreen->shop, game);
            break;
        default:
            break;
    }

    // Stones.
    Texture stoneTexture = game->assets.textures[STONE_TEXTURE];

    DrawTexturePro(
        stoneTexture,
        (Rectangle){5.0, 5.0, stoneTexture.width, stoneTexture.height},
        (Rectangle){0.0, 0.0, 35.0, 35.0},
        (Vector2){0.0, 0.0},
        0.0,
        WHITE
    );

    char stonesBuf[30];
    snprintf(stonesBuf, sizeof(stonesBuf), "%d", game->stones);
    DrawText(stonesBuf, 40.0, 5.0, 30, BLACK);

    //DrawFPS(0, 0);
}

void closeGameScreen(GameScreen* gameScreen)
{
    closeAnimation(&gameScreen->buttonPanelSharedAnimation);
    closeShop(&gameScreen->shop);
}

