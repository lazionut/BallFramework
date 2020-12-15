#pragma once
#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "Score.h"
#include "ScreenScale.h"
#include <SDL_ttf.h>
#include <vector>

class Pong : public Game
{
public:
	Pong(uint16_t width, uint16_t height, TTF_Font* font, uint32_t flags = 0, uint16_t maxFPS = 0);

private:
	void Start() override;
	void OnClose() override;
	void CheckCollision() override;
	void Update() override;
	void KeyPressed(const SDL_Keycode& key) override;
	void KeyReleased(const SDL_Keycode& key) override;
	void MousePressed(const SDL_MouseButtonEvent& mouse) override;
	void MouseReleased(const SDL_MouseButtonEvent& mouse) override;
	void Render(SDL_Renderer* renderer) override;
 
	void CheckBallWallCollision();
	void CheckPaddleWallCollision();
	void CheckBallPaddleCollision();
	void CheckBallBrickCollision();
	void CheckScoreCondition();
	
	void InitialiseBricks();
	void RenderBricks(SDL_Renderer* renderer);
	void RenderPlayersScore(SDL_Renderer* renderer);
	void ResetBall();

	Paddle m_pongPaddle1;
	Paddle m_pongPaddle2;
	std::vector<std::vector<Rectangle>> m_bricks;
	Ball m_pongBall;
	SDL_Texture* m_ballImage;
	TTF_Font* m_font;
	Score m_pongScore1;
	Score m_pongScore2;
};