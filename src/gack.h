#include "gameCommon.h"

#ifndef GACK_H
#define GACK_H

#define GACK_NAME_MAX 256

typedef struct GackEntry GackEntry;
typedef void (*GackEntryCB)(GackEntry* entry, Game* game);

typedef struct GackEntry {
    char description;
    int cost;
    GackEntryCB callback;
} GackEntry;

typedef struct Gack {
} Gack;

void initGack(Gack* gack);
void updateGack(Gack* gack, Game* game);
void closeGack(Gack* gack);

#endif
