#include "KeyActionMap.h"

KeyActionMap::KeyActionMap() {
}

KeyActionMap::~KeyActionMap() {
}

void KeyActionMap::Clear() {
	keyActionMap.clear();
}

void KeyActionMap::InsertKeyAction(SDL_Keycode key, const std::string& label) {
	if (keyActionMap.find(key) != keyActionMap.end()) { return; }

	keyActionMap.emplace(key, label);
}

void KeyActionMap::SetAction(SDL_Keycode key, const std::string& label) {
	if (keyActionMap.find(key) == keyActionMap.end()) { return; }

	keyActionMap[key] = label;
}

bool KeyActionMap::IskeyMapped(SDL_Keycode key) const {
	if (keyActionMap.find(key) != keyActionMap.end()) {
		return true;
	}
	return false;
}

std::string KeyActionMap::GetAction(SDL_Keycode key) const {
	auto it = keyActionMap.find(key);
	auto pair = *it;
	return pair.second;
}
