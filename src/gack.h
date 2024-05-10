#include "gameCommon.h"

#ifndef GACK_H
#define GACK_H

typedef struct Gack {
} Gack;

void initGack(Gack* gack);
void updateGack(Gack* gack, Game* game);
void closeGack(Gack* gack);

#endif
