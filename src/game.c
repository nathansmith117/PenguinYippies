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

    game->screenTexture = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void updateGame(Game* game)
{
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
    UnloadRenderTexture(game->screenTexture);

    CloseWindow();
}
