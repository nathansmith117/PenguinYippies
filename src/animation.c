#include "animation.h"
#include "game.h"
#include <raylib.h>

AnimationAsset loadAnimationAssetFromFile(const char* fileName)
{
    AnimationAsset animationAsset;
    animationAsset.image = LoadImageAnim(fileName, &animationAsset.frameCount);

    return animationAsset;
}

void freeAnimationAsset(AnimationAsset* animationAsset)
{
    UnloadImage(animationAsset->image);
}

Animation createAnimation(AnimationAsset* asset, double delay)
{
    Animation animation;

    animation.frameCount = asset->frameCount;
    animation.currentFrame = 0;

    animation.asset = asset;
    animation.texture = LoadTextureFromImage(asset->image);

    animation.width = asset->image.width;
    animation.height = asset->image.height;

    animation.delay = delay;
    animation.lastTime = -1.0; // -1.0 for no last time.

    animation.playing = false;

    return animation;
}

void closeAnimation(Animation* animation)
{
    UnloadTexture(animation->texture);
}

void setAnimationFrame(Animation* animation, int frame)
{
    animation->currentFrame = frame;
    unsigned int nextFrameDataOffset = animation->width * animation->height * 4 * frame;

    UpdateTexture(animation->texture, ((unsigned char*)animation->asset->image.data) + nextFrameDataOffset);
}

void runAnimation(Animation* animation)
{
    if (!animation->playing)
    {
        return;
    }

    double currentTime = GetTime();

    if (animation->lastTime == -1.0 || currentTime - animation->lastTime >= animation->delay)
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

void playAnimation(Animation* animation)
{
    animation->playing = true;
    animation->lastTime = -1.0;
}

void pauseAnimation(Animation* animation)
{
    animation->playing = false;
}

void toggleAnimation(Animation* animation)
{
    animation->playing = !animation->playing;
    animation->lastTime = -1.0;
}
