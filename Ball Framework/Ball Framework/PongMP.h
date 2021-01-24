#pragma once
#include <SDL_ttf.h>

#include "BallGame.h"

namespace BallFramework
{

	class PongMP : public BallGame
	{
	public:
		PongMP(uint16_t width, uint16_t height, uint32_t flags = 0, uint16_t maxFPS = 0);

	private:
		void Start() override;
		void OnClose() override;
		void CheckCollision() override;
		void Render(SDL_Renderer* renderer) override;

		void CreatePickUp(const Vector2& position) override;

	private:
		void CheckPaddleWallCollision();
		void CheckBallWallCollision();
		void CheckBallPaddleCollision();
		void CheckBallBrickCollision();
		void CheckScoreCondition();

		void InitializeBricks();
		void InitializeScore();
		void InitializePongMPObjects();
		void LoadPongMPImages();
	private:
		uint8_t m_bricksNumber;

		std::string m_player1Name;
		std::string m_player2Name;
	};

}