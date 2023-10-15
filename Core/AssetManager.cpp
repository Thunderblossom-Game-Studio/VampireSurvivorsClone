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
