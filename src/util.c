#include "util.h"
#include "game.h"

Vector2 getScaledMousePosition()
{
    Vector2 mousePosition = GetMousePosition();
    mousePosition.x *= (float)WINDOW_WIDTH / GetScreenWidth();
    mousePosition.y *= (float)WINDOW_HEIGHT / GetScreenHeight();

    return mousePosition;
}

bool doesCollideWithAnimationData(Rectangle rect, void* data, int width, int height, int frame, Vector2 point)
{
    // Doesn't collide with rect.
    if (!CheckCollisionPointRec(point, rect))
    {
        return false;
    }

    float xScale = (float)width / rect.width;
    float yScale = (float)height / rect.height;

    int row = (point.y - rect.y) * yScale;
    int col = (point.x - rect.x) * xScale;

    unsigned int frameOffset = width * height * frame;

    // Position of the apha byte in the color.
    unsigned int position = (frameOffset + (width * row + col)) * 4 + 3;

    // Check apha at position.
    if (*(((unsigned char*)data) + position) != 0x00)
    {
        return true;
    }

    return false;
}
