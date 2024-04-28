#include "AssetStore.h"

#include <iostream>
#include <SDL_image.h>

AssetStore::AssetStore() {
	std::cout << "ASSETSTORE: Se ejecuta constructor" << std::endl;
	if (TTF_Init() < 0) {
		std::cout << "Error al inicializar SDL_TTF" << std::endl;
		return;
	}
}

AssetStore::~AssetStore() {
	std::cout << "ASSETSTORE: Se ejecuta destructor" << std::endl;
	this->ClearAssets();
}

void AssetStore::ClearAssets() {
	for (auto texture : textures) {
		SDL_DestroyTexture(texture.second);
	}
	textures.clear();
	for (auto font : fonts) {
		TTF_CloseFont(font.second);
	}
	fonts.clear();
	TTF_Quit();
}

void AssetStore::AddTexture(const std::string& assetId,
	const std::string& filepath, SDL_Renderer* renderer) {
	SDL_Surface* surface = IMG_Load(filepath.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	textures.emplace(assetId, texture);
}

void AssetStore::AddFont(const std::string& assetId, 
	const std::string& filepath, size_t sizeFont, SDL_Renderer* renderer) {
	TTF_Font* font = TTF_OpenFont(filepath.c_str(), sizeFont);
	fonts.emplace(assetId, font);
}

SDL_Texture* AssetStore::GetTexture(const std::string& assetId) {
	return textures[assetId];
}

TTF_Font* AssetStore::GetFont(const std::string& assetId) {
	return fonts[assetId];
}
