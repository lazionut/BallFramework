#pragma once
#include <SDL_ttf.h>
#include <optional>
#include "Game.h"
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

	class BrickBreaker : public Game
	{
	public:
		BrickBreaker(uint16_t width, uint16_t height, TTF_Font* font, const std::vector<std::string>& playersNames, uint32_t flags = 0, uint16_t maxFPS = 0);

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
		void ResetBall();

		void CheckPaddleWallCollision();
		void CheckBallPaddleCollision();
		void CheckBallWallCollision();
		void CheckBallBrickCollision();
		void CheckPickUpCollision();

		void InitializeBricks();
		void RenderBricks(SDL_Renderer* renderer);

		void InitializeHearts();
		void RenderHearts(SDL_Renderer* renderer);

		void CreatePickUp(const Vector2& position);

		void RenderScore(SDL_Renderer* renderer);

		void RenderButton(SDL_Renderer* renderer);
		bool IsInBounds(Sint32 x, Sint32 y);
		void Pause();

	private: //SDL objects
		SDL_Renderer* m_renderer;
		SDL_Texture* m_ballImage;
		SDL_Texture* m_pickUpImage;
		SDL_Texture* m_heartImage;
		TTF_Font* m_font;

	private: //objects
		Paddle m_paddle;
		Ball m_ball;

		std::vector<std::vector<Rectangle>> m_bricks;

		PickUpGenerator m_pickUpGenerator;
		PickUp m_pickUp;

		Score m_score;
		std::string m_playerName;

		std::vector<Rectangle> m_hearts;
		uint16_t m_heartCounter;

		PlayersStatistics m_playersStatistics;

		Button m_pauseButton;

	private: //primitive types
		bool m_isPickCreated;
		bool m_isPickActive;

		float m_lastTimeScale;
		bool m_isPaused;
	};

}