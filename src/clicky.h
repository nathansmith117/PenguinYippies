#include "gameCommon.h"
#include "animation.h"

#define MAX_CLICKIES 256

#ifndef CLICKY_H
#define CLICKY_H

typedef struct Clicky Clicky;
typedef void (*ClickyUpdateCB)(Game* game, Clicky* clicky);
typedef void (*ClickyFreeCB)(Clicky clicky);

// A fixable clicky clicky. There shall be many clicky clickies.
typedef struct Clicky {
    Animation animation;
    Texture* texture;
    Rectangle rect;

    void* data;
    ClickyUpdateCB updateCB;
    ClickyFreeCB freeCB;

    // Used for reacting to clicks.
    bool wasClicked;
} Clicky;

typedef struct Clickies {
    Clicky clickies[MAX_CLICKIES];
    size_t clickiesCount;
} Clickies;

void initClickies(Clickies* clickies);
void closeClickies(Clickies* clickies);
void addClickyToClickies(Clickies* clickies, Clicky clicky);
void updateClickies(Game* game, Clickies* clickies);

// A silly silly penguin lol.
Clicky createPenguinLolClicky(Game* game);

#endif

