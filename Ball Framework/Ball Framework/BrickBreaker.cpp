#include "BrickBreaker.h"

#define WIDTHUNITS 10
#define HEIGHTUNITS 10

BrickBreaker::BrickBreaker(int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
	: Game("BrickBreaker", x, y, width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS)
{

}

BrickBreaker::BrickBreaker(uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
	: Game("BrickBreaker", width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS)
{

}

void BrickBreaker::Start()
{

}

void BrickBreaker::OnClose()
{

}

void BrickBreaker::CheckCollision()
{

}

void BrickBreaker::Update()
{

}

void BrickBreaker::KeyPressed(const SDL_Keycode& key)
{

}

void BrickBreaker::KeyReleased(const SDL_Keycode& key)
{

}

void BrickBreaker::Render(SDL_Renderer* renderer)
{

}
