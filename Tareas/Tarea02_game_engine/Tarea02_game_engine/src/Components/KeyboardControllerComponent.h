#pragma once

struct KeyboardControllerComponent {
	bool up;
	bool right;
	bool down;
	bool left;

	KeyboardControllerComponent(bool up = false, bool right = false, 
		bool down = false, bool left = false) {
		this->up = up;
		this->right = right;
		this->down = down;
		this->left = left;
	}
};