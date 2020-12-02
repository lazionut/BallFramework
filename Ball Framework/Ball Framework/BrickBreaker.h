#pragma once
#include "Game.h"

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

};

