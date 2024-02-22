#include "clicky.h"
#include "game.h"
#include "assets.h"
#include "util.h"

void initClickies(Clickies* clickies)
{
    clickies->clickiesCount = 0;
}

void closeClickies(Clickies* clickies)
{
    for (int i = 0; i < clickies->clickiesCount; ++i)
    {
        // Yes, we shall free it using a callback it stores.
        // Just wish I could free myself like this ):
        clickies->clickies[i].freeCB(clickies->clickies[i]);
    }
}

void updateClickies(Game* game, Clickies* clickies)
{
    for (int i = 0; i < clickies->clickiesCount; ++i)
    {
        clickies->clickies[i].updateCB(game, &clickies->clickies[i]);
    }
}

void updatePenguinLol(Game* game, Clicky* clicky)
{
    // Do clicky clicky.
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (doesCollideWithAnimationData(clicky->rect, clicky->animation.asset->image.data,
            clicky->animation.width, clicky->animation.height, clicky->animation.currentFrame, getScaledMousePosition()))
        {
            replayAnimation(&clicky->animation);
        }
    }

    // Drag around.
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        if (IsCursorOnScreen())
        {
            Vector2 mouseDelta = GetMouseDelta();
            clicky->rect.x += mouseDelta.x;
            clicky->rect.y += mouseDelta.y;
        }
    }

    // Run animation and update.
    runAnimation(&clicky->animation);

    Texture texture = clicky->animation.texture;
    DrawTexturePro(texture, (Rectangle){0.0, 0.0, texture.width, texture.height},
                   clicky->rect, Vector2Zero(), 0.0, WHITE);
}

void freePenginLolClicky(Clicky clicky)
{
    closeAnimation(&clicky.animation);
}

Clicky createPenguinLolClicky(Game* game)
{
    Clicky clicky;

    clicky.animation = createAnimation(&game->assets.animations[PENGUIN_LOL_ANIMATION], ANIMATION_DEFAULT_DELAY);
    setAnimationFrame(&clicky.animation, clicky.animation.frameCount - 1);
    clicky.animation.repeat = false;
    clicky.texture = NULL;
    clicky.rect = (Rectangle){0.0, 0.0, 512, 512};

    clicky.data = NULL;
    clicky.updateCB = updatePenguinLol;
    clicky.freeCB = freePenginLolClicky;

    clicky.wasClicked = false;

    return clicky;
}
