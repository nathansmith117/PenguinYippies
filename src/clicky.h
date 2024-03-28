#include "gameCommon.h"
#include "animation.h"

#define MAX_CLICKIES 256

#define CLICKER_DEFAULT_DELAY 0.5

#ifndef CLICKY_H
#define CLICKY_H

typedef struct Clicky Clicky;
typedef void (*ClickyUpdateCB)(Game* game, Clicky* clicky);
typedef void (*ClickyFreeCB)(Clicky clicky);

typedef enum ClickyType {
    PENGUIN_LOL_TYPE,
    CLICKER_TYPE
} ClickyType;

// A fixable clicky clicky. There shall be many clicky clickies.
typedef struct Clicky {
    ClickyType type;

    Animation animation;
    Texture* texture;
    Rectangle rect;

    void* data;
    ClickyUpdateCB updateCB;
    ClickyFreeCB freeCB;

    // Used for reacting to clicks.
    bool wasClicked;
} Clicky;

// ittle thingy used by the clicker
typedef struct Clicker {
    double timeLastClicked;
    double delay;
} Clicker;

typedef struct Clickies {
    Clicky clickies[MAX_CLICKIES];
    size_t clickiesCount;
} Clickies;

void initClickies(Clickies* clickies);
void closeClickies(Clickies* clickies);
void addClickyToClickies(Clickies* clickies, Clicky clicky);
void removeClickyFromClickies(Clickies* clickies, int id);
void updateClickies(Game* game, Clickies* clickies);

// A silly silly penguin lol.
Clicky createPenguinLolClicky(Game* game);

// Create a clicker.
Clicky createClickerClicky(Game* game);

#endif

