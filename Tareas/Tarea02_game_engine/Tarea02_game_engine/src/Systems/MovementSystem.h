#pragma once

#include "../ECS/ECS.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TagComponent.h"

#include "../EventManager/EventManager.h"
#include "../Events/OutOfLimitEvent.h"
#include <iostream>

class MovementSystem : public System {
public:
	MovementSystem() {
		RequireComponent<RigidbodyComponent>();
		RequireComponent<TransformComponent>();
	}

	void SubscribeToOutOfLimitEvent(std::shared_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<MovementSystem, OutOfLimitEvent>(this,
			&MovementSystem::OnOutOfLimitEvent);
	}

	void OnOutOfLimitEvent(OutOfLimitEvent& e) {
		e.bullet.Kill();
	}

	void Update(std::shared_ptr<EventManager>& eventManager, float deltaTyme, size_t windowWidth, size_t windowHeight) {
		for (auto entity : GetSystemEntities()) {
			auto& rigidbody = entity.GetComponent<RigidbodyComponent>();
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();
			auto& tag = entity.GetComponent<TagComponent>();

			//Verificacion de rebotes y bordes
			if (tag.tag == 1 /*Enemys*/) {
				if (transform.position.x + sprite.width >= windowWidth
					|| transform.position.x <= 0.0) {
					rigidbody.velocity.x = rigidbody.velocity.x * -1;
				}
				if (transform.position.y + sprite.height >= windowHeight
					|| transform.position.y <= 0.0) {
					rigidbody.velocity.y = rigidbody.velocity.y * -1;
				}
				transform.position += rigidbody.velocity * deltaTyme;
			}else if (tag.tag == 0 /*Player*/) {
				if ((transform.position.y >= 0 || rigidbody.velocity.y > 0)
					&& (transform.position.y + (sprite.height * transform.scale.y) <= windowHeight || rigidbody.velocity.y < 0)) {
					transform.position.y += rigidbody.velocity.y * deltaTyme;

				}				
				if ((transform.position.x >= 0 || rigidbody.velocity.x > 0)
					&& (transform.position.x + (sprite.width * transform.scale.x) <= windowWidth || rigidbody.velocity.x < 0)) {
					transform.position.x += rigidbody.velocity.x * deltaTyme;

				}
			}else if (tag.tag == 2 /*Bullet*/) {
				if (transform.position.x >= windowWidth
					|| transform.position.x - (sprite.width * transform.scale.x) <= 0
					|| transform.position.y >= windowHeight
					|| transform.position.y - (sprite.height * transform.scale.y) <= 0) {
					std::cout << "Muero" << std::endl;
					eventManager->EmitteEvent<OutOfLimitEvent>(entity);
				}else{
					transform.position += rigidbody.velocity * deltaTyme;
				}
			}
		}
	}
};
