#include "Pong.h"

Pong::Pong() : Game()
{

}

Pong::Pong( int x, int y, int width, int height, bool fullscreen, uint16_t maxFPS) :
	Game("Pong", x, y, width, height, fullscreen, maxFPS)
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