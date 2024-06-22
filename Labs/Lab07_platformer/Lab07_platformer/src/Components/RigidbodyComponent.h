#pragma once

#include <string>
#include <glm/glm.hpp>

struct RigidbodyComponent {
	bool isStatic;

	glm::vec2 sumForces = glm::vec2(0);
	glm::vec2 acceleration = glm::vec2(0);
	glm::vec2 velocity = glm::vec2(0);
	glm::vec2 jumpForce;

	float speed;

	float mass;
	float invMass;

	bool onGround = false;

	RigidbodyComponent(bool isStatic = true, float mass = 0, float speed = 0,
		glm::vec2 jumpForce = glm::vec2(0)) {
		this->isStatic = isStatic;
		this->mass = mass;
		this->invMass = 1 / mass;
		this->speed = speed;

		this->jumpForce = jumpForce;
	}
};