#pragma once

#include "BallGame.h"

namespace BallFramework
{

	class BrickBreaker : public BallGame
	{
	public:
		BrickBreaker(uint16_t width, uint16_t height, uint32_t flags = 0, uint16_t maxFPS = 0);

	private:
		void Start() override;
		void OnClose() override;
		void CheckCollision() override;
		void Render(SDL_Renderer* renderer) override;

		void CreatePickUp(const Vector2& position) override;

	private:
		void ResetBall();

		void CheckPaddleWallCollision();
		void CheckBallPaddleCollision();
		void CheckBallWallCollision();
		void CheckBallBrickCollision();

		void InitializeBricks();
		void InitializeHearts();
		void LoadBrickBreakerImages();
		void InitializeBrickBreakerObjects();
		void RenderHearts(SDL_Renderer* renderer);

	private:
		std::string m_playerName;

		std::vector<Rectangle> m_hearts;
		uint8_t m_heartCounter;
		uint16_t m_brickCounter;

	};

}