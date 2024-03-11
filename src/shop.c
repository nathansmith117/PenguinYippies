#include "shop.h"
#include "game.h"
#include "assets.h"

// Callbacks.
void createPenguinLolCB(Game* game)
{

}

void initShop(Shop* shop, Game* game)
{
    Assets* assets = &game->assets;

    // Entries.
    shop->penguinLol = LoadTextureFromImage(assets->animations[PENGUIN_LOL_ANIMATION].image);
    shop->entries[0] = (ShopEntry){&shop->penguinLol, 10, createPenguinLolCB};
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

    // Entry rects.
    double startX = 150.0;
    double startY = 80.0;
    double width = 100.0;
    double height = 100.0;

    Rectangle rects[SHOP_ENTRY_COUNT] = {
        (Rectangle){startX, startY, width, height}
    };

    // Entries.
    for (int i = 0; i < SHOP_ENTRY_COUNT; ++i)
    {
        Texture entryTexture = *shop->entries[i].texture;

        DrawTexturePro(
            entryTexture,
            (Rectangle){0.0, 0.0, entryTexture.width, entryTexture.height},
            rects[i],
            (Vector2){0.0, 0.0},
            0.0,
            WHITE
        );

        DrawRectangleLinesEx(rects[i], 2, BLACK);
    }
}

void closeShop(Shop* shop)
{
    UnloadTexture(shop->penguinLol);
}
