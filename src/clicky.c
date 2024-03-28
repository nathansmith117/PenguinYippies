#include "clicky.h"
#include "game.h"
#include "assets.h"
#include "util.h"
#include <math.h>
#include <raylib.h>
#include <raymath.h>

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

void addClickyToClickies(Clickies* clickies, Clicky clicky)
{
    if (clickies->clickiesCount >= MAX_CLICKIES)
    {
        return; // At max.
    }

    ++clickies->clickiesCount;
    clickies->clickies[clickies->clickiesCount - 1] = clicky;
}

void removeClickyFromClickies(Clickies* clickies, int id)
{
    // Free clicky.
    clickies->clickies[id].freeCB(clickies->clickies[id]);

    // Move things back.
    for (int i = id; i < clickies->clickiesCount - 1; ++i)
    {
        clickies->clickies[i] = clickies->clickies[i + 1];
    }

    --clickies->clickiesCount;
}

void updateClickies(Game* game, Clickies* clickies)
{
    for (int i = 0; i < clickies->clickiesCount; ++i)
    {
        clickies->clickies[i].updateCB(game, &clickies->clickies[i]);
    }
}

// Penguin lol methods.
void updatePenguinLol(Game* game, Clicky* clicky)
{
    // Mouse clicky.
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (doesCollideWithAnimationData(clicky->rect, clicky->animation.asset->image.data,
            clicky->animation.width, clicky->animation.height, clicky->animation.currentFrame, getScaledMousePosition()))
        {
            clicky->wasClicked = true;
        }
    }

    // Was clicked.
    if (clicky->wasClicked)
    {
        replayAnimation(&clicky->animation);
        ++game->stones;
        clicky->wasClicked = false;
    }

    // Drag around.
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        if (IsCursorOnScreen() && doesCollideWithAnimationData(clicky->rect, clicky->animation.asset->image.data,
            clicky->animation.width, clicky->animation.height, clicky->animation.currentFrame, getScaledMousePosition()))
        {
            Vector2 mouseDelta = GetMouseDelta();
            clicky->rect.x += mouseDelta.x;
            clicky->rect.y += mouseDelta.y;
        }
    }

    // Run animation and draw.
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

    clicky.type = PENGUIN_LOL_TYPE;
    clicky.animation = createAnimation(&game->assets.animations[PENGUIN_LOL_ANIMATION], ANIMATION_DEFAULT_DELAY);
    setAnimationFrame(&clicky.animation, clicky.animation.frameCount - 1);
    clicky.animation.repeat = false;
    clicky.texture = NULL;
    clicky.rect = (Rectangle){0.0, 0.0, 400.0, 400.0};

    clicky.data = NULL;
    clicky.updateCB = updatePenguinLol;
    clicky.freeCB = freePenginLolClicky;

    clicky.wasClicked = false;

    return clicky;
}

// Clicker methods.
void updateClicker(Game* game, Clicky* clicky)
{
    Clicker* clicker = (Clicker*)clicky->data;

    // Drag around.
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        if (IsCursorOnScreen() && doesCollideWithAnimationData(clicky->rect, clicky->animation.asset->image.data,
            clicky->animation.width, clicky->animation.height, clicky->animation.currentFrame, getScaledMousePosition()))
        {
            Vector2 mouseDelta = GetMouseDelta();
            clicky->rect.x += mouseDelta.x;
            clicky->rect.y += mouseDelta.y;
        }
    }

    // Collides with a other clicky.
    double currentTime = GetTime();

    if (currentTime - clicker->timeLastClicked >= clicker->delay)
    {
        Clickies* clickies = &game->clickies;

        float cloestDistance = WINDOW_WIDTH * 2.0;
        Clicky* closestClicky = NULL;

        for (int i = 0; i < clickies->clickiesCount; ++i)
        {
            Clicky* testClicky = &clickies->clickies[i];

            // Same clicky lmao.
            if (testClicky == clicky && testClicky->type == CLICKER_TYPE)
            {
                continue;
            }

            double distance = Vector2Distance(
                (Vector2){clicky->rect.x, clicky->rect.y},
                (Vector2){testClicky->rect.x, testClicky->rect.y}
            );

            if (CheckCollisionRecs(clicky->rect, testClicky->rect) && distance < cloestDistance)
            {
                closestClicky = testClicky;
                cloestDistance = distance;
            }
        }

        // Clicker click the clicky.
        if (closestClicky != NULL)
        {
            closestClicky->wasClicked = true;
        }

        clicker->timeLastClicked = currentTime;
    }

    runAnimation(&clicky->animation);

    Texture texture = clicky->animation.texture;
    DrawTexturePro(texture, (Rectangle){0.0, 0.0, texture.width, texture.height},
                   clicky->rect, Vector2Zero(), 0.0, WHITE);
}

void freeClicker(Clicky clicky)
{
    closeAnimation(&clicky.animation);

    if (clicky.data != NULL)
    {
        YP_FREE(clicky.data);
    }
}

Clicky createClickerClicky(Game* game)
{
    Clicky clicky;

    clicky.type = CLICKER_TYPE;
    clicky.animation = createAnimation(&game->assets.animations[CLICKER_ANIMATION], ANIMATION_DEFAULT_DELAY);
    playAnimation(&clicky.animation);
    clicky.animation.repeat = true;
    clicky.texture = NULL;
    clicky.rect = (Rectangle){0.0, 0.0, 128.0, 128.0};

    // Clicker structure thingy thing.
    clicky.data = YP_MALLOC(sizeof(Clicker));

    if (clicky.data == NULL)
    {
        ALLOCATION_ERROR;
    }

    Clicker* clicker = (Clicker*)clicky.data;
    clicker->timeLastClicked = 0.0;
    clicker->delay = CLICKER_DEFAULT_DELAY;

    clicky.updateCB = updateClicker;
    clicky.freeCB = freeClicker;

    clicky.wasClicked = false;

    return clicky;
}
