#include "game.h"

void initGame(Game* game)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Penguin Yippies!");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // Assets.
    initAssets(&game->assets);

    // Screens.
    game->currentScreen = MAIN_MENU_SCREEN;
    initMainMenu(&game->mainMenu, game);
    initGameScreen(&game->gameScreen, game);
    initShooterScreeen(&game->shooterScreen, game);

    // Clickies lol.
    initClickies(&game->clickies);

    // Test clickies.
    Clicky firstClicky = createPenguinLolClicky(game);
    firstClicky.rect.x = WINDOW_WIDTH / 2.0 - firstClicky.rect.width / 2.0;
    firstClicky.rect.y = WINDOW_HEIGHT / 2.0 - firstClicky.rect.height / 2.0;
    addClickyToClickies(&game->clickies, firstClicky);

    game->screenTexture = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);

    game->stones = 0;

    game->madeWithUnity = createAnimation(&game->assets.animations[MADE_WITH_UNITY_ANIMATION], 0.2);
    game->madeWithUnity.repeat = false;
    playAnimation(&game->madeWithUnity);
}

void updateGame(Game* game)
{
    if (game->madeWithUnity.playing)
    {
        runAnimation(&game->madeWithUnity);

        BeginDrawing();

        DrawTexturePro(
            game->madeWithUnity.texture,
            (Rectangle){0.0, 0.0, game->madeWithUnity.width, game->madeWithUnity.height},
            (Rectangle){0.0, 0.0, GetScreenWidth(), GetScreenHeight()},
            Vector2Zero(),
            0.0,
            WHITE
        );

        EndDrawing();

        return;
    }

    // Draw screen.
    BeginTextureMode(game->screenTexture);

    switch (game->currentScreen)
    {
        case MAIN_MENU_SCREEN:
            updateMainMenu(&game->mainMenu, game);
            break;
        case GAME_SCREEN:
            updateGameScreen(&game->gameScreen, game);
            break;
        case SHOOTER_SCREEN:
            updateShooterScreen(&game->shooterScreen, game);
            break;
        default:
            break;
    }

    EndTextureMode();

    // Draw the silly silly render texture.
    BeginDrawing();

    DrawTexturePro(
        game->screenTexture.texture,
        (Rectangle){0.0, 0.0, game->screenTexture.texture.width, -game->screenTexture.texture.height},
        (Rectangle){0.0, 0.0, GetScreenWidth(), GetScreenHeight()},
        Vector2Zero(),
        0.0,
        WHITE
    );

    EndDrawing();
}

void closeGame(Game* game)
{
    closeAssets(&game->assets);
    closeMainMenu(&game->mainMenu);
    closeGameScreen(&game->gameScreen);
    closeShooterScreen(&game->shooterScreen);
    closeClickies(&game->clickies);
    UnloadRenderTexture(game->screenTexture);

    closeAnimation(&game->madeWithUnity);

    CloseWindow();
}
