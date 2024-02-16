#include "gameCommon.h"
#include "animation.h"

#define ASSETS_NAME_MAX 100

#define TEXTURE_ASSET_COUNT 4
#define ANIMATION_ASSET_COUNT 2

#ifndef ASSETS_H
#define ASSETS_H

// Stores the names of all the assets used.
extern const char textureAssetsNames[TEXTURE_ASSET_COUNT][ASSETS_NAME_MAX];
extern const char animationAssetsNames[ANIMATION_ASSET_COUNT][ASSETS_NAME_MAX];

enum
{
    MAIN_SCREEN_BACKGROUND_TEXTURE,
    PENGUIN_BACKGROUND_BACKGROUND,
    TO_EMPERORS_EMPORIUM_ICON_TEXTURE,
    TO_GAME_ICON_TEXTURE
};

enum
{
    BUTTON_BOX_ANIMATION,
    PENGUIN_LOL_ANIMATION
};

typedef struct Assets {
    Texture textures[TEXTURE_ASSET_COUNT];
    AnimationAsset animations[ANIMATION_ASSET_COUNT];
} Assets;

void initAssets(Assets* assets);
void closeAssets(Assets* assets);

#endif
