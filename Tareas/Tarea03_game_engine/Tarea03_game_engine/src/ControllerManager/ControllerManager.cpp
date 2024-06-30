#include "ControllerManager.h"

ControllerManager::ControllerManager() {
}

ControllerManager::~ControllerManager() {
}

void ControllerManager::Clear() {
	keyActionMap.clear();
}

void ControllerManager::AddKeyAction(SDL_Keycode key, const std::string& action) {
	keyActionMap.emplace(key, action);
	actionActiveMap.emplace(action, false);
}

void ControllerManager::SetAction(SDL_Keycode key, const std::string& action) {
	auto it = keyActionMap.find(key);
	if (it != keyActionMap.end()) {
		auto pair = *it;
		actionActiveMap.erase(pair.second);
		keyActionMap[key] = action;
		actionActiveMap.emplace(action, false);
	}
}

bool ControllerManager::IskeyMapped(SDL_Keycode key) const {
	if (keyActionMap.find(key) != keyActionMap.end()) {
		return true;
	}
	return false;
}

std::string ControllerManager::GetAction(SDL_Keycode key) const {
	auto it = keyActionMap.find(key);
	if (it != keyActionMap.end()) {
		auto pair = *it;
		return pair.second;
	}
	return "none";
}

bool ControllerManager::IsActionMapped(const std::string& action) const {
	auto it = actionActiveMap.find(action);
	if (it != actionActiveMap.end()) {
		return true;
	}
	return false;
}

bool ControllerManager::GetActionState(const std::string& action) const {
	auto it = actionActiveMap.find(action);
	if (it != actionActiveMap.end()) {
		auto pair = *it;
		return pair.second;
	}
	return false;
}

void ControllerManager::ActivateAction(const std::string& action) {
	auto it = actionActiveMap.find(action);
	if (it != actionActiveMap.end()) {
		actionActiveMap[action] = true; 
	}
}

void ControllerManager::DeactivateAction(const std::string& action) {
	auto it = actionActiveMap.find(action);
	if (it != actionActiveMap.end()) {
		actionActiveMap[action] = false;
	}
}
