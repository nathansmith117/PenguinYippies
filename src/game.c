#include "game.h"

void initGame(Game* game)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Penguin Yippies!");
}

void updateGame(Game* game)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawFPS(0, 0);

    EndDrawing();
}

void closeGame(Game* game)
{
    CloseWindow();
}
