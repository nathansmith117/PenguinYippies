#include "gameCommon.h"
#include "animation.h"

#ifndef UTIL_H
#define UTIL_H

// Scale from the window to render texture.
Vector2 getScaledMousePosition();

// Check pixals and that fun stuff.
bool doesCollideWithAnimationData(Rectangle rect, void* data, int width, int height, int frame, Vector2 point);

#endif
