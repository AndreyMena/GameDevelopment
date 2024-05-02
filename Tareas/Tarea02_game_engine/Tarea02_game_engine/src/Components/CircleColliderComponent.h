 #pragma once

struct CircleColliderComponent {
	float radius;

	CircleColliderComponent(float radius = 0) {
		this->radius = radius;
	}
};