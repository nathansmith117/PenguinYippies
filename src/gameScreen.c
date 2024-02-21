#include "gameScreen.h"
#include "game.h"
#include "assets.h"

void initGameScreen(GameScreen* gameScreen, Game* game)
{
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

    // Clickies.
    gameScreen->penguinLol = createPenguinLolClicky(game);
    gameScreen->penguinLol.rect.x = WINDOW_WIDTH / 2.0 - 128.0;
    gameScreen->penguinLol.rect.y = WINDOW_HEIGHT / 2.0 - 128.0;
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

    // Button panel.
    runAnimation(&gameScreen->buttonPanelSharedAnimation);
    updateTexturedButton(&gameScreen->upgradesButton);
    updateTexturedButton(&gameScreen->achievementsButton);
    updateTexturedButton(&gameScreen->rebirthButton);
    updateTexturedButton(&gameScreen->statisticsButton);

    // update clickies.
    updateClicky(game, &gameScreen->penguinLol);
}

void closeGameScreen(GameScreen* gameScreen)
{
    closeAnimation(&gameScreen->buttonPanelSharedAnimation);
    freePenginLolClicky(gameScreen->penguinLol);
}

