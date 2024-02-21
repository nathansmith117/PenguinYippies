#include "gameCommon.h"
#include "animation.h"

#ifndef CLICKY_H
#define CLICKY_H

typedef struct Clicky Clicky;
typedef void (*ClickyUpdateCB)(Game* game, Clicky* clicky);

// A fixable clicky clicky. There shall be many clicky clickies.
typedef struct Clicky {
    Animation animation;
    Texture* texture;
    Rectangle rect;

    void* data;
    ClickyUpdateCB updateCB;
} Clicky;

void updateClicky(Game* game, Clicky* clicky);

// A silly silly penguin lol.
Clicky createPenguinLolClicky(Game* game);
void freePenginLolClicky(Clicky clicky);

#endif

