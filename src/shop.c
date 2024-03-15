#include "shop.h"
#include "game.h"
#include "assets.h"
#include "util.h"
#include "clicky.h"
#include <raylib.h>

// Callbacks.
void createPenguinLolCB(ShopEntry* entry, Game* game)
{
    SetRandomSeed(clock());

    int randomX = GetRandomValue(200, WINDOW_WIDTH - 200);
    int randomY = GetRandomValue(200, WINDOW_HEIGHT - 200);

    Clicky lol = createPenguinLolClicky(game);
    lol.rect.x = randomX;
    lol.rect.y = randomY;

    addClickyToClickies(&game->clickies, lol);
}

void createClicker(ShopEntry* entry, Game* game)
{
    SetRandomSeed(clock());

    int randomX = GetRandomValue(200, WINDOW_WIDTH - 200);
    int randomY = GetRandomValue(200, WINDOW_HEIGHT - 200);

    Clicky clicker = createClickerClicky(game);

    addClickyToClickies(&game->clickies, clicker);
}

void initShop(Shop* shop, Game* game)
{
    Assets* assets = &game->assets;

    // Entries.
    shop->penguinLol = LoadTextureFromImage(assets->animations[PENGUIN_LOL_ANIMATION].image);
    shop->entries[0] = (ShopEntry){&shop->penguinLol, 50, createPenguinLolCB};

    shop->clicker = LoadTextureFromImage(assets->animations[CLICKER_ANIMATION].image);
    shop->entries[1] = (ShopEntry){&shop->clicker, 70, createClicker};
}

void buyThingFromShop(Shop* shop, int id, Game* game)
{
    int cost = shop->entries[id].cost;

    if (game->stones >= cost)
    {
        shop->entries[id].callback(&shop->entries[id], game);
        game->stones -= cost;
    }
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
        (Rectangle){startX, startY, width, height},
        (Rectangle){startX, startY + height, width, height}
    };

    // Entries.
    for (int i = 0; i < SHOP_ENTRY_COUNT; ++i)
    {
        Texture entryTexture = *shop->entries[i].texture;

        // Draw the entry texture.
        DrawTexturePro(
            entryTexture,
            (Rectangle){0.0, 0.0, entryTexture.width, entryTexture.height},
            rects[i],
            (Vector2){0.0, 0.0},
            0.0,
            WHITE
        );

        Color outlineColor = BLACK;

        // Test collision.
        if (CheckCollisionPointRec(getScaledMousePosition(), rects[i]))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                buyThingFromShop(shop, i, game);
            }
            else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                outlineColor = BLUE;
            }
        }

        // Draw outline.
        DrawRectangleLinesEx(rects[i], 2, outlineColor);

        // Draw cost.
        char costBuf[20];
        int cost = shop->entries[i].cost;
        snprintf(costBuf, sizeof(costBuf), "%d", cost);

        Color costColor = BLACK;

        if (cost > game->stones)
        {
            costColor = RED;
        }

        DrawText(costBuf, rects[i].x + rects[i].width + 2, rects[i].y + 10, 50, costColor);
    }
}

void closeShop(Shop* shop)
{
    UnloadTexture(shop->penguinLol);
    UnloadTexture(shop->clicker);
}
