#include "util.h"
#include "game.h"

Vector2 getScaledMousePosition()
{
    Vector2 mousePosition = GetMousePosition();
    mousePosition.x *= (float)WINDOW_WIDTH / GetScreenWidth();
    mousePosition.y *= (float)WINDOW_HEIGHT / GetScreenHeight();

    return mousePosition;
}

bool doesCollideWithAnimation(Rectangle rect, Animation* animation, Vector2 point)
{
    float xScale = (float)rect.width / animation->width;
    float yScale = (float)rect.height / animation->height;

    unsigned int frameOffset = animation->width * animation->height * 4 * animation->currentFrame;

    // Check each pixal.
    for (int row = 0; row < rect.height; ++row)
    {
        for (int col = 0; col < rect.width; ++col)
        {
            int scaledRow = row * yScale;
            int scaledCol = col * xScale;

            int pixalPosition = frameOffset + (animation->width * scaledRow + scaledCol);

        }
    }

    return false;
}
