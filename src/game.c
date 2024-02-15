#include "game.h"

void initGame(Game* game)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Penguin Yippies!");

    // Assets.
    initAssets(&game->assets);

    // Screens.
    game->currentScreen = MAIN_MENU_SCREEN;
    initMainMenu(&game->mainMenu, game);
    initGameScreen(&game->gameScreen, game);
}

void updateGame(Game* game)
{
    BeginDrawing();

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

    EndDrawing();
}

void closeGame(Game* game)
{
    closeAssets(&game->assets);
    closeMainMenu(&game->mainMenu);
    closeGameScreen(&game->gameScreen);

    CloseWindow();
}
