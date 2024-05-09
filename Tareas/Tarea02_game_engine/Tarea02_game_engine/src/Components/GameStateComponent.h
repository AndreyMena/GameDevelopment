#pragma once
#include <string>

struct GameStateComponent {
	std::string assetGameOver;
	
	// 0 for run, 1 for game over
	int state;

	GameStateComponent(std::string assetGameOver = "", int state = 0)
		: assetGameOver(assetGameOver), state(state) {}
};