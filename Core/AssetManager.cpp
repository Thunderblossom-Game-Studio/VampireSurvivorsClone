#include "AssetManager.h"
#include "../Rendering/RenderInstanceManager.h"

AssetManager::AssetManager(token) 
{}

AssetManager::~AssetManager() 
{
	for (const auto& pair : _textureCatalogue)
		SDL_DestroyTexture(pair.second);
	_textureCatalogue.clear();
}

SDL_Texture* AssetManager::LoadImage(std::string file)
{
	// Check the catalogue, if there's already a texture from this directory, return that.
	std::map<std::string, SDL_Texture*>::iterator it;
	it = _textureCatalogue.find(file);
	if (it != _textureCatalogue.end()) 
		return _textureCatalogue[file];

	// Attempt to load the file and create an SDL_Texture from it.
	SDL_Surface* loadedSurface = IMG_Load(file.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Surface failed to load filepath: " << file << std::endl;
		return nullptr;
	}
	SDL_Texture* loadedTexture = SDL_CreateTextureFromSurface(
		RenderInstanceManager::instance().GetRenderer("main")->GetRenderer(), loadedSurface);	
	SDL_FreeSurface(loadedSurface);
	if (loadedTexture == NULL)
	{
		std::cout << "Failed to create texture: " << file << std::endl;
		return nullptr;
	}

	// If successful, add it to the catalogue for future cases and return the texture.
	_textureCatalogue.insert(std::make_pair(file, loadedTexture));
	return loadedTexture;
}


TTF_Font* AssetManager::LoadFont(std::string file)
{
	std::map<std::string, TTF_Font*>::iterator it;
	it = _fontCatalogue.find(file);
	if (it != _fontCatalogue.end())
		return _fontCatalogue[file];

	// Attempt to load the file and create a TTF_Font from it.
	TTF_Font* font = TTF_OpenFont(file.c_str(), 32);

	if (!font)
	{
		std::cout << "Could not load font" << std::endl;
		return nullptr;
	}

	// If successful, add it to the catalogue for future cases and return the texture.
	_fontCatalogue.insert(std::make_pair(file, font));
	return font;
}