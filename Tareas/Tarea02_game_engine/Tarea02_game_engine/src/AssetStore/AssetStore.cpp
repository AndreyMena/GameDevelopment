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
	for (auto texture : images) {
		SDL_DestroyTexture(texture.second.texture);
	}
	images.clear();
	for (auto font : fonts) {
		TTF_CloseFont(font.second);
	}
	fonts.clear();
	TTF_Quit();
}

void AssetStore::AddTexture(const std::string& assetId,
	const std::string& filepath, SDL_Renderer* renderer, int width, int height) {
	Image image;
	SDL_Surface* surface = IMG_Load(filepath.c_str());
	image.texture = SDL_CreateTextureFromSurface(renderer, surface);
	image.width = width;
	image.textureId = assetId;
	image.height = height;
	SDL_FreeSurface(surface);

	images.emplace(assetId, image);
}

void AssetStore::AddFont(const std::string& assetId, 
	const std::string& filepath, size_t sizeFont, SDL_Renderer* renderer) {
	TTF_Font* font = TTF_OpenFont(filepath.c_str(), sizeFont);
	fonts.emplace(assetId, font);
}

SDL_Texture* AssetStore::GetTexture(const std::string& assetId) {
	return images[assetId].texture;
}

Image AssetStore::GetImage(const std::string& assetId) {
	return images[assetId];
}

TTF_Font* AssetStore::GetFont(const std::string& assetId) {
	return fonts[assetId];
}
