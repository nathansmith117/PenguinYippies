#include "gameCommon.h"
#include <raylib.h>

#define ANIMATION_DEFAULT_DELAY 0.1

#ifndef ANIMATION_H
#define ANIMATION_H

// The asset is what is loaded from a file and the animation is like a instance of it.

typedef struct AnimationAsset {
    // The animation is stored in a image and the texture is used for fast rendering.
    int frameCount;
    Image image;
} AnimationAsset;

typedef struct Animation {
    // Frame stuff.
    int frameCount;
    int currentFrame;

    AnimationAsset* asset;
    Texture texture;

    int width;
    int height;

    // Timing the frames.
    double delay;
    double lastTime;
} Animation;

AnimationAsset loadAnimationAssetFromFile(const char* fileName);
void freeAnimationAsset(AnimationAsset* animationAsset);

Animation createAnimation(AnimationAsset* asset, double delay);
void closeAnimation(Animation* animation);

// Set the frame and update the texture.
void setAnimationFrame(Animation* animation, int frame);

void runAnimation(Animation* animation);
void pauseAnimation(Animation* animation);

#endif
