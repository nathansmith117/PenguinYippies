#include "gameCommon.h"

#ifndef GACK_H
#define GACK_H

#define GACK_NAME_MAX 256
#define GACK_ENTRY_COUNT 2

typedef struct GackEntry GackEntry;
typedef void (*GackEntryCB)(GackEntry* entry, Game* game);

// A entry for a upgrade.
typedef struct GackEntry {
    char description[GACK_NAME_MAX];
    int cost;
    GackEntryCB callback;
} GackEntry;

typedef struct Gack {
    GackEntry entries[GACK_ENTRY_COUNT];
} Gack;

void initGack(Gack* gack);
void updateGack(Gack* gack, Game* game);
void closeGack(Gack* gack);

#endif
