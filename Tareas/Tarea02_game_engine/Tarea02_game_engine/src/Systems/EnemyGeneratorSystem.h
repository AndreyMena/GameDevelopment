#pragma once

#include "../ECS/ECS.h"
#include "../Components/EnemyGeneratorComponent.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../Util/Image.h"

class EnemyGeneratorSystem : public System {
	size_t windowWidth;
	size_t windowHeight;
public:
	EnemyGeneratorSystem(size_t windowWidth, size_t windowHeight) : 
		windowWidth(windowWidth), windowHeight(windowHeight) {
		RequireComponent<EnemyGeneratorComponent>();
	}

	void Update(float deltaTime, std::shared_ptr<ECSManager>& manager) {
		for (auto entity : GetSystemEntities()) {
			auto& enemyGenerator = entity.GetComponent<EnemyGeneratorComponent>();
			if (entity.GetId() == 1) {
			}
			// Actualiza el tiempo transcurrido desde el último spawn de enemigo
			enemyGenerator.timeSinceLastSpawn += deltaTime;


			// Realiza el spawn de un nuevo enemigo si ha pasado suficiente tiempo
			if (enemyGenerator.timeSinceLastSpawn >= (enemyGenerator.spawnRate / 1000)) {
				std::cout << enemyGenerator.timeSinceLastSpawn << std::endl;
				SpawnEnemy(enemyGenerator, manager); // Función para generar un nuevo enemigo
				enemyGenerator.timeSinceLastSpawn = 0; // Reinicia el contador
			}
		}
	}

	void SpawnEnemy(EnemyGeneratorComponent& enemyGenerator, std::shared_ptr<ECSManager>& manager) {
		float speed = rand() % enemyGenerator.maxSpeed + enemyGenerator.minSpeed;
		float speedX = rand() % enemyGenerator.maxSpeed + enemyGenerator.minSpeed;
		float speedY = rand() % enemyGenerator.maxSpeed + enemyGenerator.minSpeed;

		float scale = 2.0;
		glm::vec2 position;
		int maxWidth = windowWidth - (enemyGenerator.image.width * scale);
		int maxHeight = windowHeight - (enemyGenerator.image.height * scale);
		position.x = rand() % maxWidth;
		position.y = rand() % maxHeight;
		//std::cout << position.x << " " << position.y << std::endl;

		Entity enemy = manager->CreateEntity();
		enemy.AddComponent<CircleColliderComponent>(16.0f);
		enemy.AddComponent<RigidbodyComponent>(glm::vec2(speedX, speedY), speed);
		enemy.AddComponent<SpriteComponent>(enemyGenerator.image.textureId, 
			enemyGenerator.image.width, enemyGenerator.image.height, 
			enemyGenerator.image.width, 0);
		enemy.AddComponent<TransformComponent>(position,
			glm::vec2(scale, scale), 0);

		enemy.AddComponent<EnemyGeneratorComponent>(
			enemyGenerator.image.textureId, enemyGenerator.image, enemyGenerator.score,
			enemyGenerator.minSpeed, enemyGenerator.maxSpeed, enemyGenerator.spawnRate, 0.0);
	}
};
