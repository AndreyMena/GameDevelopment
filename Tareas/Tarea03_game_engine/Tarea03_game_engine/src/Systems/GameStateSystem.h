#pragma once

#include "../Game/Game.h"
#include "../ECS/ECS.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"

#include "../AssetStore/AssetStore.h"
#include "../EventManager/EventManager.h"
#include "../Events/LevelEvent.h"
#include <iostream>
#include <string>
#include <SDL.h>

class GameStateSystem : public System {
	std::string assetGameOver;
public:
	int state = 0;
	bool nextLevel = false;
	GameStateSystem() {
		//RequireComponent<RigidbodyComponent>();
		//RequireComponent<TransformComponent>();
	}

	void SubscribeToOnLevelEvent(std::shared_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<GameStateSystem, LevelEvent>(this,
			&GameStateSystem::OnLevelEvent);
	}

	void OnLevelEvent(LevelEvent& e) {
		//state = 1;
		//assetGameOver = e.a.GetComponent<GameStateComponent>().assetGameOver;
		if (e.levelEvent == "win_event") {
			nextLevel = true;
			//Game::GetInstance().NextLevel();
		}
	}

	void Update(SDL_Renderer* renderer, std::shared_ptr<AssetStore>& assetStore,
		size_t windowWidth, size_t windowHeight) {
		if (nextLevel) {
			nextLevel = false;
			Game::GetInstance().NextLevel();
		}
		/*
		if (state == 1) {
			int widht = 300;
			int height = 100;
			SDL_Rect txtDstRect = {
				(windowWidth / 2) - (widht / 2),
				(windowHeight / 2) - (height / 2),
				widht,
				height
			};

			SDL_Color fontColor = { 255, 0, 0 };
			SDL_Surface* txtSurface = TTF_RenderText_Solid(assetStore->GetFont("press-start-30-game-over"),
				"Game Over",
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
		*/
	}
};
