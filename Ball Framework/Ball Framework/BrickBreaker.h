#pragma once
#include <SDL_ttf.h>
#include <optional>
#include "Game.h"
#include "BallGame.h"
#include "ScreenScale.h"
#include "Paddle.h"
#include "Ball.h"
#include "PickUpGenerator.h"
#include "Score.h"
#include "Button.h"
#include "PlayersStatistics.h"
#include "Paths.h"

namespace BallFramework
{

	class BrickBreaker : public BallGame
	{
	public:
		BrickBreaker(uint16_t width, uint16_t height, TTF_Font* font, const std::vector<std::string>& playersNames, uint32_t flags = 0, uint16_t maxFPS = 0);

	private: //override Game class methods
		void Start() override;
		void OnClose() override;
		void CheckCollision() override;
		void Render(SDL_Renderer* renderer) override;

	private: //class methods
		void ResetBall();

		void CheckPaddleWallCollision();
		void CheckBallPaddleCollision();
		void CheckBallWallCollision();
		void CheckBallBrickCollision();

		void InitializeBricks();

		void InitializeHearts();
		void RenderHearts(SDL_Renderer* renderer);

		void CreatePickUp(const Vector2& position) override;

	private:
		SDL_Texture* m_heartImage;

		Score m_score;
		std::string m_playerName;

		std::vector<Rectangle> m_hearts;
		uint8_t m_heartCounter;
		uint16_t m_brickCounter;

	};

}