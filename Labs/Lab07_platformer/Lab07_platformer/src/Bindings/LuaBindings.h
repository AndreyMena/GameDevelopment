#pragma once

#include "../game/Game.h"

#include <string>

bool GetActionState(const std::string action) {
	return Game::GetInstance().controllerManager->GetActionState(action);
}



