#pragma once
#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "Score.h"
#include "ScreenScale.h"
#include <SDL_ttf.h>

class Pong : public Game
{
public:
	Pong(uint16_t width, uint16_t height, uint32_t flags = 0, uint16_t maxFPS = 0);

private:
	void Start() override;
	void OnClose() override;
	void CheckCollision() override;
	void Update() override;
	void KeyPressed(const SDL_Keycode& key) override;
	void KeyReleased(const SDL_Keycode& key) override;
	void Render(SDL_Renderer* renderer) override;

	void RenderPlayersScore(SDL_Renderer* renderer);

	Paddle m_pongPaddle1;
	Paddle m_pongPaddle2;
	Ball m_pongBall;
	SDL_Texture* m_ballImage;
	Score m_pongScore1;
	Score m_pongScore2;
};