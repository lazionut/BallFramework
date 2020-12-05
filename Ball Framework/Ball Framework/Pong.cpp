#include "Pong.h"
#include <SDL_ttf.h> 

#define WIDTHUNITS 20
#define HEIGHTUNITS 10

Pong::Pong(int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
	: Game("Pong", x, y, width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS)
{

}

Pong::Pong(uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
	: Game("Pong", width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS)
{

}

void Pong::Start()
{
	
}

void Pong::OnClose()
{

}

void Pong::CheckCollision()
{
	
}

void Pong::Update()
{
	
}

void Pong::KeyPressed(const SDL_Keycode& key)
{
	
}

void Pong::KeyReleased(const SDL_Keycode& key)
{
	
}

void Pong::Render(SDL_Renderer* renderer)
{
	
}