#pragma once
#include <SDL_ttf.h>
#include "Game.h"
#include "BallGame.h"
#include "Brick.h"
#include "Game.h"
#include "ScreenScale.h"
#include "Paddle.h"
#include "Ball.h"
#include "PickUpGenerator.h"
#include "Score.h"
#include "Button.h"
#include "Paths.h"
#include "PlayersStatistics.h"

namespace BallFramework
{

	class PongMP : public BallGame
	{
	public:
		PongMP(uint16_t width, uint16_t height, TTF_Font* font, const std::vector<std::string>& playersNames, uint32_t flags = 0, uint16_t maxFPS = 0);

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
		void CheckPickUpCollision();
		void CheckScoreCondition();

		void InitializeBricks();

		void CreatePickUp(const Vector2& position);

		void RenderPlayersScore(SDL_Renderer* renderer);

	private: //SDL objects
		SDL_Renderer* m_renderer;

	private: //objects
		uint16_t m_bricksNumber;

		std::string m_player1Name;
		std::string m_player2Name;

		Score m_player1Score;
		Score m_player2Score;
	};

}