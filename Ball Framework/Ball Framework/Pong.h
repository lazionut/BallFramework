#pragma once
#include <SDL_ttf.h>
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

	class Pong : public Game
	{
	public:
		Pong(uint16_t width, uint16_t height, TTF_Font* font, const std::string& player1Name, const std::string& player2Name, uint32_t flags = 0, uint16_t maxFPS = 0);

	private: //override Game class methods
		void Start() override;
		void Update() override;
		void OnClose() override;
		void CheckCollision() override;
		void KeyPressed(const SDL_Keycode& key) override;
		void KeyReleased(const SDL_Keycode& key) override;
		void MousePressed(const SDL_MouseButtonEvent& mouse) override;
		void MouseReleased(const SDL_MouseButtonEvent& mouse) override;
		void Render(SDL_Renderer* renderer) override;

	private: //class methods
		void CheckPaddleWallCollision();
		void CheckBallWallCollision();
		void CheckBallPaddleCollision();
		void CheckBallBrickCollision();
		void CheckPickUpCollision();
		void CheckScoreCondition();

		void InitializeBricks();
		void RenderBricks(SDL_Renderer* renderer);

		void CreatePickUp(const Vector2& position);

		void RenderPlayersScore(SDL_Renderer* renderer);

		void RenderButton(SDL_Renderer* renderer);
		bool IsInBounds(Sint32 x, Sint32 y);
		void Pause();

	private: //SDL objects
		SDL_Renderer* m_renderer;
		SDL_Texture* m_ballImage;
		SDL_Texture* m_pickUpImage;
		TTF_Font* m_font;

	private: //objects
		Paddle m_paddlePlayer1;
		Paddle m_paddlePlayer2;

		Ball m_ball;

		std::vector<std::vector<Rectangle>> m_bricks;
		uint16_t m_bricksNumber;

		PickUpGenerator m_pickUpGenerator;
		PickUp m_pickUp;

		Score m_scorePlayer1;
		Score m_scorePlayer2;

		std::string m_player1Name;
		std::string m_player2Name;

		PlayersStatistics m_playersStatistics;

		Button m_pauseButton;

	private: //primitive types
		bool m_isPickCreated;
		bool m_isPickActive;

		float m_lastTimeScale;
		bool m_isPaused;
	};

}