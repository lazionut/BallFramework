#include "BrickBreaker.h"

BrickBreaker::BrickBreaker() : Game()
{

}

BrickBreaker::BrickBreaker(const char* title, int x, int y, int width, int height, bool fullscreen, uint16_t maxFPS) :
	Game(title, x, y, width, height, fullscreen, maxFPS)
{
}

BrickBreaker::BrickBreaker(const std::string& title, int x, int y, int width, int height, bool fullscreen, uint16_t maxFPS) :
	Game(title, x, y, width, height, fullscreen, maxFPS)
{
}

void BrickBreaker::start()
{
}

void BrickBreaker::checkCollision()
{
}

void BrickBreaker::update()
{
}

void BrickBreaker::keyPressed(const SDL_Keycode& key)
{
}

void BrickBreaker::keyReleased(const SDL_Keycode& key)
{
}

void BrickBreaker::render(SDL_Renderer* renderer)
{
}
