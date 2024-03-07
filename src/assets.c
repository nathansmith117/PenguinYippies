#include "assets.h"
#include <raylib.h>

const char textureAssetsNames[TEXTURE_ASSET_COUNT][ASSETS_NAME_MAX] = {
    "mainScreenBackground.png",
    "penguinBackground.png",
    "toEmperorsEmporiumIcon.png",
    "toGameIcon.png",
    "emperorShopUI.png",
    "shopBoard.png"
};

const char animationAssetsNames[ANIMATION_ASSET_COUNT][ASSETS_NAME_MAX] = {
    "buttonBox.gif",
    "penguinLol.gif"
};

void loadTextures(Assets* assets)
{
    for (int i = 0; i < TEXTURE_ASSET_COUNT; ++i)
    {
        char filePath[ASSETS_NAME_MAX];
        snprintf(filePath, ASSETS_NAME_MAX, "assets/%s", textureAssetsNames[i]);
        assets->textures[i] = LoadTexture(filePath);
    }
}

void loadAnimations(Assets* assets)
{
    for (int i = 0; i < ANIMATION_ASSET_COUNT; ++i)
    {
        char filePath[ASSETS_NAME_MAX];
        snprintf(filePath, ASSETS_NAME_MAX, "assets/%s", animationAssetsNames[i]);
        assets->animations[i] = loadAnimationAssetFromFile(filePath);
    }
}

// Used for setting different options in assets like animation delay.
void configureAssets(Assets* assets)
{
}

void initAssets(Assets* assets)
{
    TraceLog(LOG_INFO, "Loading assets");

    loadTextures(assets);
    loadAnimations(assets);
    configureAssets(assets);

    TraceLog(LOG_INFO, "Assets loaded");
}

void closeAssets(Assets* assets)
{
    TraceLog(LOG_INFO, "Closing assets");

    // Textures.
    for (int i = 0; i < TEXTURE_ASSET_COUNT; ++i)
    {
        UnloadTexture(assets->textures[i]);
    }

    // Animations.
    for (int i = 0; i < ANIMATION_ASSET_COUNT; ++i)
    {
        freeAnimationAsset(&assets->animations[i]);
    }

    TraceLog(LOG_INFO, "Assets closed");
}
