#pragma once
#include "Game.h"

class Pong : public Game
{
public:
	Pong();
	Pong(const char* title, int x, int y, int width, int height, bool fullscreen, uint16_t maxFPS = 0);
	Pong(const std::string& title, int x, int y, int width, int height, bool fullscreen, uint16_t maxFPS = 0);

private:
	void start() override;
	void checkCollision() override;
	void update() override;
	void keyPressed(const SDL_Keycode& key) override;
	void keyReleased(const SDL_Keycode& key) override;
	void render(SDL_Renderer* renderer) override;
};