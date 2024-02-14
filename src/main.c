#include "gameCommon.h"
#include "game.h"
#include <raylib.h>

int main(int argc, char** argv)
{
    Game game;
    initGame(&game);

    while (!WindowShouldClose())
    {
        updateGame(&game);
    }

    closeGame(&game);
    return 0;
}
