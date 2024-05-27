#pragma once

#include <map>
#include <SDL.h>
#include <string>

class KeyActionMap {
	std::map<SDL_Keycode, std::string> keyActionMap;

public:
	KeyActionMap();
	~KeyActionMap();

	void Clear();
	void InsertKeyAction(SDL_Keycode key,  const std::string& label);
	void SetAction(SDL_Keycode key,  const std::string& label);
	bool IskeyMapped(SDL_Keycode key) const;
	std::string GetAction(SDL_Keycode key) const;
};

