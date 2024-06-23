#pragma once

#include <map>
#include <SDL.h>
#include <string>

class ControllerManager {
	std::map<SDL_Keycode, std::string> keyActionMap;
	std::map<std::string, bool> actionActiveMap;

public:
	ControllerManager();
	~ControllerManager();

	void Clear();

	void AddKeyAction(SDL_Keycode key,  const std::string& action);
	void SetAction(SDL_Keycode key,  const std::string& action);
	bool IskeyMapped(SDL_Keycode key) const;
	std::string GetAction(SDL_Keycode key) const;
	bool IsActionMapped(const std::string& action) const;
	bool GetActionState(const std::string& action) const;
	void ActivateAction(const std::string& action);
	void DeactivateAction(const std::string& action);
};

