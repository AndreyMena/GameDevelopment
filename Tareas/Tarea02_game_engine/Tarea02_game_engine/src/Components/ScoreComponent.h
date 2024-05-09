#pragma once

#include <string>
#include <SDL.h>

struct ScoreComponent {
	int score;

	ScoreComponent(int score = 0) {
		this->score = score;
	}
};