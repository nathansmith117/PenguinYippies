#include "clicky.h"
#include "game.h"
#include "assets.h"

void updatePenguinLol(Game* game, Clicky* clicky)
{

}

Clicky createPenguinLolClicky(Game* game)
{
    Clicky clicky;

    clicky.animation = createAnimation(&game->assets.animations[PENGUIN_LOL_ANIMATION], ANIMATION_DEFAULT_DELAY);
    clicky.texture = &clicky.animation.texture;
    clicky.rect = (Rectangle){0.0, 0.0, 128.0, 128.0};

    clicky.data = NULL;
    clicky.updateCB = updatePenguinLol;

    runAnimation(&clicky.animation);

    return clicky;
}

void freePenginLolClicky(Clicky clicky)
{
    closeAnimation(&clicky.animation);
}
