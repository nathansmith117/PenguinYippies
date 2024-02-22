#include "clicky.h"
#include "game.h"
#include "assets.h"
#include "util.h"

void updateClicky(Game* game, Clicky* clicky)
{
    clicky->updateCB(game, clicky);
}

void updatePenguinLol(Game* game, Clicky* clicky)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (doesCollideWithAnimationData(clicky->rect, clicky->animation.asset->image.data,
            clicky->animation.width, clicky->animation.height, clicky->animation.currentFrame, getScaledMousePosition()))
        {
            replayAnimation(&clicky->animation);
        }
    }

    // Run animation and update.
    runAnimation(&clicky->animation);

    Texture texture = clicky->animation.texture;
    DrawTexturePro(texture, (Rectangle){0.0, 0.0, texture.width, texture.height},
                   clicky->rect, Vector2Zero(), 0.0, WHITE);
}

Clicky createPenguinLolClicky(Game* game)
{
    Clicky clicky;

    clicky.animation = createAnimation(&game->assets.animations[PENGUIN_LOL_ANIMATION], ANIMATION_DEFAULT_DELAY);
    setAnimationFrame(&clicky.animation, 0);
    clicky.animation.repeat = false;
    clicky.texture = NULL;
    clicky.rect = (Rectangle){0.0, 0.0, 512, 512};

    clicky.colors = LoadImageColors(game->assets.animations[PENGUIN_LOL_ANIMATION].image);

    clicky.data = NULL;
    clicky.updateCB = updatePenguinLol;

    return clicky;
}

void freePenginLolClicky(Clicky clicky)
{
    closeAnimation(&clicky.animation);
    UnloadImageColors(clicky.colors);
}
