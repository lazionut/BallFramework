#pragma once
#include "Game.h"
#include "Rectangle.h"
#include "Ball.h"

class TestGame : public Game
{
public:
	TestGame(uint16_t width, uint16_t height, uint32_t flags = 0, uint16_t maxFPS = 0);

private:

	void Start() override;
	void OnClose() override;
	void CheckCollision() override;
	void Update() override;
	void KeyPressed(const SDL_Keycode& key) override;
	void KeyReleased(const SDL_Keycode& key) override;
	void Render(SDL_Renderer* renderer) override;


	Ball ball;
	Rectangle rect;
	SDL_Texture* ballImage;
	SDL_Color color;
};
