#pragma once

#include "../Templates/Singleton.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include <SDL_ttf.h>

class AssetManager final : public Singleton<AssetManager> 
{
private:
    /// @brief The texture catalogue that stores all loaded textures.
    std::map<std::string, SDL_Texture*> _textureCatalogue;
    std::map<std::string, TTF_Font*> _fontCatalogue;

public:
    AssetManager(token);
    ~AssetManager();

    /// <summary>
    /// Attempts to load an image and store it in the texture catalogue,
    /// if it's already in the catalogue it will return that value.
    /// </summary>
    /// <param name="file">The filepath trying to be accessed.</param>
    /// <returns>A texture if one is found, nullptr if other.</returns>
    SDL_Texture* LoadImage(std::string file);
    TTF_Font* LoadFont(std::string file);
};