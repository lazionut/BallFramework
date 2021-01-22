#pragma once
#include <SDL_ttf.h>

#include "Game.h"
#include "Paddle.h"
#include "Ball.h"
#include "PickUpGenerator.h"
#include "Score.h"
#include "Button.h"
#include "PlayersStatistics.h"
#include "Paths.h"
#include "Colors.h"
#include "Brick.h"
#include "Random.h"

namespace BallFramework
{
	class BallGame : public Game
	{
	public:
		BallGame(const std::string& title, uint16_t width, uint16_t height, TTF_Font* font, uint32_t flags = 0, uint16_t maxFPS = 0, uint16_t widthUnit = 10, uint16_t heightUnit = 10);

		void SetPlayers(const std::vector<std::string>& players);

		const inline static GeneratorData defaultGeneratorData{ 2.0f, 5.0f, 1.0f, 5.0f, 2.0f, 5 };

	protected:
		//void SetPaddlesColors(const SDL_Color& paddleColor, const SDL_Color& outlineColor, const float outlineSize);

		void Pause();

		bool IsMouseOnButton(Sint32 x, Sint32 y);

		void RenderPaddles(SDL_Renderer* renderer);
		void RenderGameObjects(SDL_Renderer* renderer);
		void RenderButton(SDL_Renderer* renderer);
		void RenderBricks(SDL_Renderer* renderer);
		void RenderScore(SDL_Renderer* renderer);

		void CheckPickUpCollision();

		virtual void CreatePickUp(const Vector2& position) = 0;

	protected:
		TTF_Font* m_buttonFont;

		float m_lastTimeScale;
		bool m_isPaused;
		std::vector<float> m_outlineSizes;
		std::vector<SDL_Color> m_paddleColors;
		std::vector<SDL_Color> m_paddleOutlines;

	protected:
		std::vector<Paddle> m_players;
		std::vector<Ball> m_balls;
		std::vector<std::vector<Brick>> m_bricks;
		std::vector<Score> m_scores;

		PickUpGenerator m_pickUpGenerator;
		PickUp m_pickUp;

		Button m_pauseButton;

		std::vector<std::string> m_playersNames;
		PlayersStatistics m_playersStatistics;

		SDL_Texture* m_ballImage;
		std::vector<SDL_Texture*> m_ballImages;
		SDL_Texture* m_pickUpImage;

	private:
		void Update() override final;
		void KeyPressed(const SDL_Keycode& key) override final;
		void KeyReleased(const SDL_Keycode& key) override final;
		void MousePressed(const SDL_MouseButtonEvent& mouse) override final;
		void MouseReleased(const SDL_MouseButtonEvent& mouse) override final;
	};
}