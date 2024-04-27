#include "AssetStore.h"

#include <iostream>
#include <SDL_image.h>

AssetStore::AssetStore() {
	std::cout << "ASSETSTORE: Se ejecuta constructor" << std::endl;
}

AssetStore::~AssetStore() {
	std::cout << "ASSETSTORE: Se ejecuta destructor" << std::endl;
}

void AssetStore::ClearAssets() {
	for (auto texture : textures) {
		SDL_DestroyTexture(texture.second);
	}
	textures.clear();
}

void AssetStore::AddTexture(const std::string& assetId,
	const std::string& filepath, SDL_Renderer* renderer) {
	SDL_Surface* surface = IMG_Load(filepath.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	textures.emplace(assetId, texture);
}

SDL_Texture* AssetStore::GetTexture(const std::string& assetId)
{
	return textures[assetId];
}
