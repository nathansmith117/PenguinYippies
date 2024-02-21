#include "util.h"
#include "game.h"

Vector2 getScaledMousePosition()
{
    Vector2 mousePosition = GetMousePosition();
    mousePosition.x *= (float)WINDOW_WIDTH / GetScreenWidth();
    mousePosition.y *= (float)WINDOW_HEIGHT / GetScreenHeight();

    return mousePosition;
}
