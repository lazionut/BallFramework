#include "Pong.h"

Pong::Pong() : Game()
{

}

Pong::Pong(const char* title, int x, int y, int width, int height, bool fullscreen, uint16_t maxFPS) :
	Game(title, x, y, width, height, fullscreen, maxFPS)
{

}

Pong::Pong(const std::string& title, int x, int y, int width, int height, bool fullscreen, uint16_t maxFPS) :
	Game(title, x, y, width, height, fullscreen, maxFPS)
{

}

void Pong::start()
{
}

void Pong::checkCollision()
{
}

void Pong::update()
{
}

void Pong::keyPressed(const SDL_Keycode& key)
{
}

void Pong::keyReleased(const SDL_Keycode& key)
{
}

void Pong::render(SDL_Renderer* renderer)
{
}