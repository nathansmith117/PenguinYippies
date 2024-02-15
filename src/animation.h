#include "gameCommon.h"

#define ANIMATION_DEFAULT_DELAY 0.1

#ifndef ANIMATION_H
#define ANIMATION_H

typedef struct Animation {
    // Frame stuff.
    int frameCount;
    int currentFrame;

    // The animation is stored in a image and the texture is used for fast rendering.
    Image image;
    Texture texture;

    // Timing the frames.
    double delay;
    double lastTime;
} Animation;

Animation loadAnimationFromFile(const char* fileName);
void freeAnimation(Animation* animation);

// Set the frame and update the texture.
void setAnimationFrame(Animation * animation, int frame);

void runAnimation(Animation * animation);

#endif
