#include "gameCommon.h"

// The fullname is waaayyy toooo looonnnng for lazy lazy me

#define SHOP_ENTRY_COUNT 1

#ifndef SHOP_H
#define SHOP_H

typedef void (*ShopyEntryCB)(Game* game);

typedef struct ShopEntry {
    Texture* texture;
    int cost;
    ShopyEntryCB callback;
} ShopEntry;

typedef struct Shop {
    ShopEntry entries[SHOP_ENTRY_COUNT];

    // Some silly textures.
    Texture penguinLol;
} Shop;

void initShop(Shop* shop, Game* game);
void updateShop(Shop* shop, Game* game);
void closeShop(Shop* shop);

#endif
