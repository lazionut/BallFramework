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

class BallGame : public Game
{
public:

	BallGame(const std::string& title, uint16_t width, uint16_t height, TTF_Font* font, uint32_t flags, uint16_t maxFPS, uint16_t widthUnit, uint16_t heightUnit);

private: //inherited methods

	void Start() override = 0;
	void Update() override = 0;
	void OnClose() override = 0;
	void CheckCollision() override = 0;
	void KeyPressed(const SDL_Keycode& key) override = 0;
	void KeyReleased(const SDL_Keycode& key) override = 0;
	void MousePressed(const SDL_MouseButtonEvent& mouse) override = 0;
	void MouseReleased(const SDL_MouseButtonEvent& mouse) override = 0;
	void Render(SDL_Renderer* renderer) override = 0;

private: //SDL objects
	SDL_Renderer* m_renderer;
	SDL_Texture* m_ballImage;
	SDL_Texture* m_pickUpImage;
	TTF_Font* m_buttonFont;

private:// custom types

	Paddle m_player1;
	std::optional<Paddle> m_player2;

	std::vector<std::vector<Rectangle>> m_bricks;

	PickUpGenerator m_pickupgenerator;
	PickUp m_pickup;

	Button m_pauseButton;

	Score m_score1;
	std::optional<Score> m_score2;

	PlayersStatistics m_playersStatistics;

private: //primitive types
	bool m_isPickCreated;
	bool m_isPickActive;

	float m_lastTimeScale;
	bool m_isPaused;

};