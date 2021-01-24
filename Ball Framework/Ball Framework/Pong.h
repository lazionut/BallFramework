#pragma once
#include <SDL_ttf.h>

#include "BallGame.h"

namespace BallFramework
{

	class Pong : public BallGame
	{
	public:
		Pong(uint16_t width, uint16_t height, const std::vector<std::string>& playersNames, uint32_t flags = 0, uint16_t maxFPS = 0);

	private: //override Game class methods
		void Start() override;
		void OnClose() override;
		void CheckCollision() override;
		void Render(SDL_Renderer* renderer) override;

	private: //class methods
		void CheckPaddleWallCollision();
		void CheckBallWallCollision();
		void CheckBallPaddleCollision();
		void CheckBallBrickCollision();
		void CheckScoreCondition();

		void CheckBotMovement();

		void InitializeBricks();
		void InitializeScore();
		void InitializePongObjects();
		void LoadPongImages();

		void CreatePickUp(const Vector2& position) ;

	private: //objects
		uint8_t m_bricksNumber;

		std::string m_playerName;
		std::string m_botName;

		Paddle m_botPlayer;
	};

}