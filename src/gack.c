#include "gack.h"
#include "game.h"
#include "assets.h"
#include "util.h"
#include "clicky.h"

void increasePenguinLolStonesPerClick(GackEntry* entry, Game* game)
{
    ++game->clickies.settings.penguinLolStonesPerClick;
    entry->cost *= 1.5;
}

void decreaseClickerDelay(GackEntry* entry, Game* game)
{
    game->clickies.settings.clickersDelay /= 1.5;
    entry->cost *= 1.5;
}

void initGack(Gack* gack)
{
    gack->entries[0] = (GackEntry){"Increase penguin lol stones per click", 100, increasePenguinLolStonesPerClick};
    gack->entries[1] = (GackEntry){"Decrease clicker delay", 200, decreaseClickerDelay};
}

void updateGack(Gack* gack, Game* game)
{
    // Draw gack background.
    Texture gackTexture = game->assets.textures[GACK_PENGUIN_TEXTURE];

    DrawTexturePro(
        gackTexture,
        (Rectangle){0.0, 0.0, gackTexture.width, gackTexture.height},
        (Rectangle){0.0, 0.0, WINDOW_WIDTH, WINDOW_HEIGHT},
        (Vector2){0.0, 0.0},
        0.0,
        WHITE
    );

    int entryWidth = 500;
    int entryHeight = 50;
    int startX = 20;
    int startY = 70;

    // Update each entry.
    for (int i = 0; i < GACK_ENTRY_COUNT; ++i)
    {
        GackEntry* entry = &gack->entries[i];
        
        int yPosition = startY + (entryHeight * i);
        
        Rectangle rect = (Rectangle){
            startX,
            yPosition,
            entryWidth,
            entryHeight
        };

        Color outlineColor = BLACK;

         // Is clicked
        if (CheckCollisionPointRec(getScaledMousePosition(), rect))
        {
            // Clicked on it to buy.
            if (game->stones >= entry->cost && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                game->stones -= entry->cost;

                if (entry->callback != NULL)
                {
                    entry->callback(entry, game);
                }
            }

            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                outlineColor = PINK;
            }
        }

        // Draw this stupid thing.
        DrawRectangleLinesEx(rect, 2.0, outlineColor);
        DrawText(entry->description, startX + 5, yPosition + 5, 20, BLACK);

        // Draw cost.
        Color costColor = BLACK;

        if (entry->cost > game->stones)
        {
            costColor = RED;
        }
        
        char costBuf[10];
        snprintf(costBuf, sizeof(costBuf), "%d", entry->cost);
        DrawText(costBuf, startX + rect.width + 5, yPosition + 5, 40, costColor);
    }
}

void closeGack(Gack* gack)
{
}
