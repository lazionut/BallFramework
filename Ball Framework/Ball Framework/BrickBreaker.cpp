#include "BrickBreaker.h"

#define WIDTHUNITS 10
#define HEIGHTUNITS 13


BrickBreaker::BrickBreaker(int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
	: Game("BrickBreaker", x, y, width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),
	m_paddle(Vector2(0, -HEIGHTUNITS / 2 + 0.5f), 2.0f, 0.25f, Vector2::left, Vector2::right,
		SDLK_LEFT, SDLK_RIGHT, 5.0)
{

}

BrickBreaker::BrickBreaker(uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
	: Game("BrickBreaker", width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),
	m_paddle(Vector2(0, -HEIGHTUNITS / 2 + 0.5f), 2.0f, 0.25f, Vector2::left, Vector2::right,
		SDLK_LEFT, SDLK_RIGHT, 5.0)
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
	if (m_paddle.GetPosition().GetX() < -WIDTHUNITS / 2) {
		m_paddle.SetPosition(-WIDTHUNITS / 2, m_paddle.GetPosition().GetY());
	}
	if (m_paddle.GetPosition().GetX() > WIDTHUNITS / 2) {
		m_paddle.SetPosition(WIDTHUNITS / 2, m_paddle.GetPosition().GetY());
	}
}

void BrickBreaker::Update()
{
	m_paddle.Move();
}

void BrickBreaker::KeyPressed(const SDL_Keycode& key)
{
	m_paddle.KeyPressed(key);
}

void BrickBreaker::KeyReleased(const SDL_Keycode& key)
{
	m_paddle.KeyReleased(key);
}

void BrickBreaker::Render(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	GetScale().PointToPixel(rect, m_paddle.GetPosition(), m_paddle.GetWidth(), m_paddle.GetHeight());
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
}
