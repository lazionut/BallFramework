#pragma once
#include "Game.h"
#include "Ball.h"
#include "Paddle.h"

class Pong : public Game
{
public:
	Pong(int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS);
	Pong(uint16_t width, uint16_t height, uint32_t flags = 0, uint16_t maxFPS = 0);

private:
	void Start() override;
	void OnClose() override;
	void CheckCollision() override;
	void Update() override;
	void KeyPressed(const SDL_Keycode& key) override;
	void KeyReleased(const SDL_Keycode& key) override;
	void Render(SDL_Renderer* renderer) override;
};