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

void setAnimationFrame(Animation * animation, int frame)
{
    animation->currentFrame = frame;
    unsigned int nextFrameDataOffset = animation->image.width * animation->image.height * 4 * frame;

    UpdateTexture(animation->texture, ((unsigned int*)animation->image.data) + nextFrameDataOffset);
}

void runAnimation(Animation * animation)
{
    double currentTime = GetTime();

    if (animation->lastTime == -1 || currentTime - animation->lastTime >= animation->delay)
    {
        // Count the frames up.
        int newFrame = animation->currentFrame + 1;

        if (newFrame >= animation->frameCount)
        {
            newFrame = 0;
        }

        // Set the frame
        setAnimationFrame(animation, newFrame);

        animation->lastTime =  currentTime;
    }
}
