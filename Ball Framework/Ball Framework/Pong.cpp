#include "Pong.h"
#include <SDL_ttf.h> 

#define WIDTHUNITS 20
#define HEIGHTUNITS 10

Pong::Pong(int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
	: Game("Pong", x, y, width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),
	m_pongPaddle(Vector2(((WIDTHUNITS * -1) / 2 + 0.5f), 0), 3.0f, 0.5f, Vector2::up, Vector2::down, SDLK_LEFT, SDLK_RIGHT, 4)
{

}

Pong::Pong(uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
	: Game("Pong", width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),
	m_pongPaddle(Vector2(((WIDTHUNITS * -1) / 2 + 0.5f), 0), 3.0f, 0.5f, Vector2::up, Vector2::down, SDLK_LEFT, SDLK_RIGHT, 4)
{

}

void Pong::Start()
{
	m_ballImage = LoadImage("ball.png");
	if (m_ballImage == nullptr)
		Stop();
	m_pongBall.SetPosition(m_pongBall.GetPosition().GetX(), m_pongBall.GetPosition().GetY());
	m_pongBall.SetSize(0.75f);
	m_pongBall.SetDirection(1, 0);
	m_pongBall.SetSpeed(2);
}

void Pong::OnClose()
{
	SDL_DestroyTexture(m_ballImage);
}

void Pong::CheckCollision()
{
	
}

void Pong::Update()
{
	m_pongPaddle.Move();
	m_pongBall.Move();
}

void Pong::KeyPressed(const SDL_Keycode& key)
{
	m_pongPaddle.KeyPressed(key);
}

void Pong::KeyReleased(const SDL_Keycode& key)
{
	m_pongPaddle.KeyReleased(key);
}

void Pong::Render(SDL_Renderer* renderer)
{
	SDL_Rect aux;
	GetScale().PointToPixel(aux, m_pongPaddle.GetPosition(), m_pongPaddle.GetHeight(), m_pongPaddle.GetWidth());
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &aux);
	GetScale().PointToPixel(aux, m_pongBall.GetPosition(), m_pongBall.GetSize(), m_pongBall.GetSize());
	SDL_RenderCopy(renderer, m_ballImage, NULL, &aux);
}