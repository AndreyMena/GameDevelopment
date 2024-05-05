#pragma once

struct TagComponent {

	//Player = 0,
	//Enemy = 1,
	//Bullet = 2,
	int tag;

	TagComponent(int tag = 0) {
		this->tag = tag;
	}
};