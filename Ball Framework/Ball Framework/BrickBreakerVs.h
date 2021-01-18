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
	class BrickBreakerVS : public BallGame
	{
	public:
		BrickBreakerVS(uint16_t width, uint16_t height, TTF_Font* font, const std::vector<std::string>& playersNames, uint32_t flags = 0, uint16_t maxFPS = 0);

	private: //override Game class methods
		void Start() override;
		void OnClose() override;
		void CheckCollision() override;
		void Render(SDL_Renderer* renderer) override;

	private: //class methods
		void ResetBall();
		void ResetBall2();

		void CheckPaddleWallCollision();
		void CheckBallPaddleCollision();
		void CheckBallWallCollision();
		void CheckBallBrickCollision();
		void CheckPickUpCollision();

		void InitializeBricks();

		void InitializeHearts();
		void RenderHearts(SDL_Renderer* renderer);

		void CreatePickUp(const Vector2& position) override;

	private:
		SDL_Texture* m_heartImage;

		Score m_score1;
		Score m_score2;

		std::string m_player1Name;
		std::string m_player2Name;

		std::vector<Rectangle> m_hearts1;
		std::vector<Rectangle> m_hearts2;
		uint8_t m_heartCounter1;
		uint8_t m_heartCounter2;
		uint16_t m_brickCounter1;
		uint16_t m_brickCounter2;
		bool m_lastPaddleHit;
		bool m_switchBall;
	};
}