#include "gameCommon.h"

#define UI_BUTTON_NAME_MAX 50

#ifndef UI_H
#define UI_H

typedef struct TexturedButton {
    Texture* texture; // Can be in a animation or assets.
    Rectangle rect;

    char message[UI_BUTTON_NAME_MAX];

    Color backgroundColor;
    Color foregroundColor;

    bool isPressed;
} TexturedButton;

// Buttons don't need to be freed from memory. The button doesn't handle the texture memory.
TexturedButton createTexturedButton(Texture* texture, Rectangle rect, const char* message,
                                    Color backgroundColor, Color foregroundColor);
bool updateTexturedButton(TexturedButton* button);

#endif
