#pragma once

#include "../ECS/ECS.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"

class MovementSystem : public System {
public:
	MovementSystem() {
		RequireComponent<RigidbodyComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update(float deltaTyme, size_t windowWidth, size_t windowHeight) {
		for (auto entity : GetSystemEntities()) {
			auto& rigidbody = entity.GetComponent<RigidbodyComponent>();
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();

			//Verificacion de rebotes
			if (entity.GetId() != 0) {
				if (transform.position.x + sprite.width >= windowWidth
					|| transform.position.x <= 0.0) {
					rigidbody.velocity.x = rigidbody.velocity.x * -1;
				}
				if (transform.position.y + sprite.height >= windowHeight
					|| transform.position.y <= 0.0) {
					rigidbody.velocity.y = rigidbody.velocity.y * -1;
				}
				transform.position += rigidbody.velocity * deltaTyme;
			}else{
				if ((transform.position.y >= 0 || rigidbody.velocity.y > 0)
					&& (transform.position.y + (sprite.height * transform.scale.y) <= windowHeight || rigidbody.velocity.y < 0)) {
					transform.position.y += rigidbody.velocity.y * deltaTyme;

				}				
				if ((transform.position.x >= 0 || rigidbody.velocity.x > 0)
					&& (transform.position.x + (sprite.width * transform.scale.x) <= windowWidth || rigidbody.velocity.x < 0)) {
					transform.position.x += rigidbody.velocity.x * deltaTyme;

				}
			}
		}
	}
};
