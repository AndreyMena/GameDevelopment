#pragma once

#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/PointsComponent.h"
#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../Events/EnemyKilledEvent.h"
#include <memory>
#include <SDL.h>
#include <string>

class RenderScoreSystem : public System {
public:
	RenderScoreSystem() {
	}

	void SubscribeToEnemyKilledEvent(std::shared_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<RenderScoreSystem, EnemyKilledEvent>(this,
			&RenderScoreSystem::OnEnemyKilledEvent);
	}

	void OnEnemyKilledEvent(EnemyKilledEvent& e) {
		auto entities = GetSystemEntities();
		Entity score = entities[1];  // Score
		score.GetComponent<ScoreComponent>().score += e.a.GetComponent<PointsComponent>().points;
	}

	void Update(SDL_Renderer* renderer, std::shared_ptr<AssetStore>& assetStore) {
		//Score
		auto entities = GetSystemEntities();
		Entity score = entities[1];  // Score
		std::string scoreText = "Score ";
		std::string scoreInt = std::to_string(score.GetComponent<ScoreComponent>().score);
		std::string actualScore = scoreText + scoreInt;

		SDL_Rect txtDstRect = {
			20,
			20,
			50,
			20
		};

		SDL_Color fontColor = { 255, 233, 0 };
		SDL_Surface* txtSurface = TTF_RenderText_Solid(assetStore->GetFont("press-start-20-score"),
			actualScore.c_str(),
			fontColor
		);
		SDL_Texture* txtTexture = SDL_CreateTextureFromSurface(renderer, txtSurface);

		SDL_RenderCopyEx(
			renderer,
			txtTexture,
			NULL, // Si es NULL dibuja toda la textura
			&txtDstRect,
			0.0,
			NULL,
			SDL_FLIP_NONE
		);
	}
};
