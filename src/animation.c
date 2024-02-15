#include "animation.h"
#include "game.h"
#include <raylib.h>

Animation loadAnimationFromFile(const char* fileName)
{
    Animation animation;

    // Load image in.
    animation.image = LoadImageAnim(fileName, &animation.frameCount);
    animation.texture = LoadTextureFromImage(animation.image);

    // Set options.
    animation.currentFrame = 0;
    animation.delay = ANIMATION_DEFAULT_DELAY;
    animation.lastTime = -1.0; // -1.0 means there wasn't a last time.

    return animation;
}

void freeAnimation(Animation* animation)
{
    UnloadImage(animation->image);
    UnloadTexture(animation->texture);
}
