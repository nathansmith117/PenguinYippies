#include "gameCommon.h"
#include "animation.h"
#include <raylib.h>

#ifndef UTIL_H
#define UTIL_H

// Scale from the window to render texture.
Vector2 getScaledMousePosition();

// Check pixals and that fun stuff.
bool doesCollideWithAnimation(Rectangle rect, Animation* animation, Vector2 point);

#endif
