#pragma once

#include "../EventManager/Event.h"
#include <SDL.h>

class KeyboardEvent : public Event {
public:
	bool keyDown;
	SDL_Keycode keyCode;
	
	KeyboardEvent(bool keyDown = false, SDL_Keycode keyCode = SDLK_UNKNOWN) {
		this->keyDown = keyDown;
		this->keyCode = keyCode;
	}
};

