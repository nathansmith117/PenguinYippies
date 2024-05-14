#include "gameScreen.h"
#include "game.h"
#include "assets.h"
#include "util.h"
#include "clicky.h"
#include "shooterScreen.h"
#include <raylib.h>

void initGameScreen(GameScreen* gameScreen, Game* game)
{
    gameScreen->place = CLICKY_DESKTOP_PLACE;

    Assets* assets = &game->assets;
    int width = WINDOW_WIDTH;
    int height = WINDOW_HEIGHT;
    int navigationButtonSize = 100;
    int navigationButtonX = width - navigationButtonSize - 5.0;

    // Navigation buttons.
    gameScreen->toGameButton = createTexturedButton(
        &assets->textures[TO_GAME_ICON_TEXTURE],
        (Rectangle){navigationButtonX, 5.0, navigationButtonSize, navigationButtonSize},
        "",
        WHITE,
        BLACK
    );

    gameScreen->toEmperorsEmporiumButton = createTexturedButton(
        &assets->textures[TO_EMPERORS_EMPORIUM_ICON_TEXTURE],
        (Rectangle){navigationButtonX, navigationButtonSize + 15.0, navigationButtonSize, navigationButtonSize},
        "",
        WHITE,
        BLACK
    );

    gameScreen->toGackPenguinButton = createTexturedButton(
        &assets->textures[TO_GACK_ICON_TEXTURE],
        (Rectangle){navigationButtonX, (navigationButtonSize + 15.0) * 2.0, navigationButtonSize, navigationButtonSize},
        "",
        WHITE,
        BLACK
    );

    // Nap Time stuff.
    gameScreen->napTimeButton = createTexturedButton(
        &assets->textures[NAP_TIME_TEXTURE],
        (Rectangle){700.0, 5.0, 100.0, 50.0},
        "",
        WHITE,
        BLACK
    );

    gameScreen->nextShootingStoneCount = RUN_SHOOTER_GAME_COUNT_START;

    initShop(&gameScreen->shop, game);
    initGack(&gameScreen->gack);

    setGameScreenTool(gameScreen, CLICKER_TOOL);
}

void updateGameScreenClickyDesktop(GameScreen* gameScreen, Game* game)
{
    // Clickies clickies.
    updateClickies(game, &game->clickies);
}

void updateGameScreenNavigation(GameScreen* gameScreen, Game* game)
{
    // Navigation buttons.
    if (updateTexturedButton(&gameScreen->toGameButton))
    {
        gameScreen->place = CLICKY_DESKTOP_PLACE;
    }
    if (updateTexturedButton(&gameScreen->toEmperorsEmporiumButton))
    {
        gameScreen->place = SHOP_PLACE;
    }
    if (updateTexturedButton(&gameScreen->toGackPenguinButton))
    {
        gameScreen->place = GACK_PLACE;
    }
}

void setGameScreenTool(GameScreen* gameScreen, ToolId tool)
{
    gameScreen->tool = tool;

    // TODO: Switch cursor for different tools
    switch (tool)
    {
        case CLICKER_TOOL:
            break;
        case BOOPER_TOOL:
            break;
        default:
            break;
    }
}

void updateGameScreenTool(GameScreen* gameScreen, Game* game)
{
    ToolId tool = gameScreen->tool;
    Clickies* clickies = &game->clickies;

    switch (tool)
    {
        case CLICKER_TOOL:
            // Nothing lmao.
            break;
        case BOOPER_TOOL:

            for (int i = 0; i < clickies->clickiesCount; ++i)
            {
                Rectangle rect = clickies->clickies[i].rect;

                if (CheckCollisionPointRec(getScaledMousePosition(), rect))
                {
                    // Draw silly outline.
                    Color colorOptions[] = {YELLOW, PINK, BLACK, BLUE, PURPLE, MAGENTA, RED};
                    SetRandomSeed(time(NULL));
                    int colorIndex = GetRandomValue(0, sizeof(colorOptions) / sizeof(Color) - 1);
                    Color color = colorOptions[colorIndex];

                    DrawRectangleLinesEx(rect, colorIndex + 1, color);

                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        removeClickyFromClickies(clickies, i);
                    }

                    break; // Only one at a time.
                }
            }

            break;
        default:
            break;
    }
}

void updateGameScreenToolBar(GameScreen* gameScreen, Game* game)
{
    int toolIconWidth = 50;
    int toolIconHeight = 50;

    Assets* assets = &game->assets;

    Texture toolTextures[TOOL_COUNT] = {
        assets->textures[CLICKER_TOOL_TEXTURE],
        assets->textures[BOOPER_TOOL_TEXTURE]
    };

    for (int i = 0; i < TOOL_COUNT; ++i)
    {
        Rectangle rect = (Rectangle){i * toolIconWidth + 200, 0.0, toolIconWidth, toolIconHeight};
        Texture texture = toolTextures[i];

        // Draw tool texture.
        DrawTexturePro(
            texture,
            (Rectangle){0.0, 0.0, texture.width, texture.height},
            rect,
            (Vector2){0.0, 0.0},
            0.0,
            WHITE
        );

        // Outline current tool
        if (i == gameScreen->tool)
        {
            DrawRectangleLinesEx(rect, 3, BLACK);
        }
        else // Switch tools.
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(getScaledMousePosition(), rect))
            {
                setGameScreenTool(gameScreen, i);
            }
        }
    }
}

void updateGameScreen(GameScreen* gameScreen, Game* game)
{
    // Test shooter.
    // if (IsKeyPressed(KEY_S))
    // {
    //     enterShooterScreen(game);
    // }

     // Draw background.
    Texture background = game->assets.textures[MAIN_SCREEN_BACKGROUND_TEXTURE];

    DrawTexturePro(
        background,
        (Rectangle){0.0, 0.0, background.width, background.height},
        (Rectangle){0.0, 0.0, WINDOW_WIDTH, WINDOW_HEIGHT},
        (Vector2){0.0, 0.0},
        0.0,
        WHITE
    );

    // assssssss hehehe
    switch (gameScreen->place)
    {
        case CLICKY_DESKTOP_PLACE:
            updateGameScreenClickyDesktop(gameScreen, game);
            break;
        case SHOP_PLACE:
            updateShop(&gameScreen->shop, game);
            break;
        case GACK_PLACE:
            updateGack(&gameScreen->gack, game);
            break;
        default:
            break;
    }

    // Stones.
    Texture stoneTexture = game->assets.textures[STONE_TEXTURE];

    DrawTexturePro(
        stoneTexture,
        (Rectangle){5.0, 5.0, stoneTexture.width, stoneTexture.height},
        (Rectangle){0.0, 0.0, 35.0, 35.0},
        (Vector2){0.0, 0.0},
        0.0,
        WHITE
    );

    char stonesBuf[30];
    snprintf(stonesBuf, sizeof(stonesBuf), "%d", game->stones);
    DrawText(stonesBuf, 40.0, 5.0, 30, BLACK);

    // Shooter game stuff.
    if (game->stones >= gameScreen->nextShootingStoneCount)
    {

        // Show button to enter nap time.
        if (updateTexturedButton(&gameScreen->napTimeButton))
        {
            ++game->stones;
            enterShooterScreen(game);
            gameScreen->nextShootingStoneCount *= 5.0;
        }
    }

    char nextShooterBuf[60];
    snprintf(nextShooterBuf, sizeof(nextShooterBuf), "Next sleepy time is at %d stones", gameScreen->nextShootingStoneCount);
    DrawText(nextShooterBuf, 350.0, 5.0, 20, BLACK);

    updateGameScreenNavigation(gameScreen, game);
    updateGameScreenTool(gameScreen, game); // This should go before tool bar update because of how clicks work.
    updateGameScreenToolBar(gameScreen, game);
}

void closeGameScreen(GameScreen* gameScreen)
{
    closeShop(&gameScreen->shop);
}

