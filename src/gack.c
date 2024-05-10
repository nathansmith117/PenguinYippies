#include "gack.h"
#include "game.h"
#include "assets.h"

void initGack(Gack* gack)
{
}

void updateGack(Gack* gack, Game* game)
{
    Texture gackTexture = game->assets.textures[GACK_PENGUIN_TEXTURE];

    DrawTexturePro(
        gackTexture,
        (Rectangle){0.0, 0.0, gackTexture.width, gackTexture.height},
        (Rectangle){0.0, 0.0, WINDOW_WIDTH, WINDOW_HEIGHT},
        (Vector2){0.0, 0.0},
        0.0,
        WHITE
    );
}

void closeGack(Gack* gack)
{
}
