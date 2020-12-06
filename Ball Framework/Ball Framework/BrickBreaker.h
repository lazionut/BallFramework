#pragma once
#include "Game.h"
#include "Paddle.h"
#include "Score.h"
#include "Ball.h"
#include "PickUp.h"

#include <SDL_ttf.h>
#include <vector>

class BrickBreaker : public Game
{
public:
	BrickBreaker(int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS);
	BrickBreaker(uint16_t width, uint16_t height, uint32_t flags = 0, uint16_t maxFPS = 0);

private:
	void Start() override;
	void OnClose() override;
	void CheckCollision() override;
	void KeyPressed(const SDL_Keycode& key) override;
	void KeyReleased(const SDL_Keycode& key) override;
	void Render(SDL_Renderer* renderer) override;
	void Update() override;

	void InitBricks();
	void RenderBricks(SDL_Renderer* renderer);
	void CheckBrickBreakerBallWallCollision();
	void ChangeBallDirOnBrickCollision(Rectangle& rec);
	void RenderScore(SDL_Renderer* renderer);

	Paddle m_paddle;
	std::vector<std::vector<Rectangle>> m_bricks;
	Score m_score;
	SDL_Texture* m_ballImage = nullptr;
	Ball m_ball;
	PickUp BrickBreakerPickUp;
};

