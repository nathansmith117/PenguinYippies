#include "shop.h"
#include "game.h"
#include "assets.h"

void initShop(Shop* shop, Game* game)
{

}

void updateShop(Shop* shop, Game* game)
{
    Texture shopBoard = game->assets.textures[SHOP_BOARD_TEXTURE];

    // Board thingy.
    DrawTexturePro(
        shopBoard,
        (Rectangle){0.0, 0.0, shopBoard.width, shopBoard.height},
        (Rectangle){0.0, 0.0, WINDOW_WIDTH, WINDOW_HEIGHT},
        (Vector2){0.0, 0.0},
        0.0,
        WHITE
    );

    // Penguin thingy thing thing
    Texture yoyoyo = game->assets.textures[EMPEROR_SHOP_UI_TEXTURE];

     DrawTexturePro(
        yoyoyo,
        (Rectangle){0.0, 0.0, yoyoyo.width, yoyoyo.height},
        (Rectangle){0.0, 0.0, WINDOW_WIDTH, WINDOW_HEIGHT},
        (Vector2){0.0, 0.0},
        0.0,
        WHITE
    );
}

void closeShop(Shop* shop)
{

}
