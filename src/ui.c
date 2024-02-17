#include "ui.h"
#include "game.h"

TexturedButton createTexturedButton(Texture* texture, Rectangle rect, const char* message,
                                    Color backgroundColor, Color foregroundColor)
{
    TexturedButton button;
    button.texture = texture;
    button.rect = rect;
    strncpy((char*)button.message, message, UI_BUTTON_NAME_MAX);
    button.backgroundColor = backgroundColor;
    button.foregroundColor = foregroundColor;
    button.isPressed = false;

    return button;
}

bool updateTexturedButton(TexturedButton* button)
{
    // Draw the button.
    DrawTexturePro(
        *button->texture,
        (Rectangle){0.0, 0.0, button->texture->width, button->texture->height},
        button->rect,
        Vector2Zero(),
        0.0,
        button->backgroundColor
    );

    return button->isPressed;
}
