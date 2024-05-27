#include "KeyActionMap.h"

KeyActionMap::KeyActionMap() {
}

KeyActionMap::~KeyActionMap() {
}

void KeyActionMap::Clear() {
	keyActionMap.clear();
}

void KeyActionMap::MapKeyAction(SDL_KeyCode key, const std::string& label) {
	if (keyActionMap.find(key) != keyActionMap.end()) { return; }

	keyActionMap.emplace(key, label);
}

void KeyActionMap::SetAction(SDL_KeyCode key, const std::string& label) {
	if (keyActionMap.find(key) == keyActionMap.end()) { return; }

	keyActionMap[key] = label;
}

bool KeyActionMap::IskeyMapped(SDL_KeyCode key) const {
	if (keyActionMap.find(key) != keyActionMap.end()) { return true; }
	return false;
}

std::string KeyActionMap::GetAction(SDL_KeyCode key) const {
	auto it = keyActionMap.find(key);
	auto pair = *it;
	return pair.second;
}
