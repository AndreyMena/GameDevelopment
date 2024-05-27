#pragma once

#include <map>
#include <SDL.h>
#include <string>

class KeyActionMap {
	std::map<SDL_KeyCode, std::string> keyActionMap;

public:
	KeyActionMap();
	~KeyActionMap();

	void Clear();
	void MapKeyAction(SDL_KeyCode key,  const std::string& label);
	void SetAction(SDL_KeyCode key,  const std::string& label);
	bool IskeyMapped(SDL_KeyCode key) const;
	std::string GetAction(SDL_KeyCode key) const;
};

