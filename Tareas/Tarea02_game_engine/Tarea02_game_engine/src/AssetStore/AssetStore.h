#pragma once
#include <map>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "../Util/Image.h"

class AssetStore {
	std::map<std::string, Image> images;
	std::map<std::string, TTF_Font*> fonts;

public:
	AssetStore();
	~AssetStore();

	void ClearAssets();

	void AddTexture(const std::string& assetId, const std::string& filepath,
		SDL_Renderer* renderer, int width, int height);
	void AddFont(const std::string& assetId, const std::string& filepath,
		size_t sizeFont, SDL_Renderer* renderer);

	SDL_Texture* GetTexture(const std::string& assetId);
	Image GetImage(const std::string& assetId);
	TTF_Font* GetFont(const std::string& assetId);
};

