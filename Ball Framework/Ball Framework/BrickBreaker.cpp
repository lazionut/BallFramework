#include "BrickBreaker.h"

#define WIDTHUNITS 10
#define HEIGHTUNITS 13
#define BRICKROWS 7
#define BRICKPERROW 9
#define BRICKW 0.81f
#define BRICKH 0.35f
#define SPACING 0.25f
#define BRICKLIMIT_X -WIDTHUNITS / 2 + 0.75f
#define BRICKLIMIT_Y  HEIGHTUNITS / 2 - SPACING * 2

BrickBreaker::BrickBreaker(int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
	: Game("BrickBreaker", x, y, width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),
	m_paddle(Vector2(0, -HEIGHTUNITS / 2 + 0.5f), 2.0f, 0.25f, Vector2::left, Vector2::right,
		SDLK_LEFT, SDLK_RIGHT, 5.0), m_bricks {BRICKROWS}, m_score {}
{

}

BrickBreaker::BrickBreaker(uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
	: Game("BrickBreaker", width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),
	m_paddle(Vector2(0, -HEIGHTUNITS / 2 + 0.5f), 2.0f, 0.25f, Vector2::left, Vector2::right,
		SDLK_LEFT, SDLK_RIGHT, 5.0), m_bricks{ BRICKROWS }, m_score {}
{

}

void BrickBreaker::Start()
{
	InitBricks();
}

void BrickBreaker::OnClose()
{

}

void BrickBreaker::CheckCollision()
{
	if (m_paddle.GetPosition().GetX() < -WIDTHUNITS / 2 + m_paddle.GetWidth()/2 + SPACING) {
		m_paddle.SetPosition(-WIDTHUNITS / 2 + m_paddle.GetWidth()/2 + 0.25f, m_paddle.GetPosition().GetY());
	}
	if (m_paddle.GetPosition().GetX() > WIDTHUNITS / 2 - m_paddle.GetWidth()/2 - SPACING) {
		m_paddle.SetPosition(WIDTHUNITS / 2 - m_paddle.GetWidth()/2 - 0.25f, m_paddle.GetPosition().GetY());
	}
}

void BrickBreaker::Update()
{
	m_paddle.Move();
}

void BrickBreaker::InitBricks()
{
	float offset = 0.5f;
	float x = BRICKLIMIT_X, y = BRICKLIMIT_Y;

	for (int i = 0; i < BRICKROWS; i++) 
	{
		m_bricks[i].resize(BRICKPERROW);
		for (int j = 0; j < BRICKPERROW; j++) 
		{
				m_bricks[i][j].Set(Vector2(x,y), BRICKW, BRICKH);
				x = x + SPACING + BRICKW;
		}
		x = BRICKLIMIT_X;
		y -= offset;
	}
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
	RenderBricks(renderer);
	RenderScore(renderer);
}

void BrickBreaker::RenderBricks(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	ScreenScale scale = GetScale();
	for (const auto& iter1 : m_bricks) {
		for (const auto& iter2 : iter1) {
			scale.PointToPixel(rect, iter2.GetPosition(), iter2.GetWidth(), iter2.GetHeight());
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}

void BrickBreaker::RenderScore(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	SDL_Texture* font = m_score.GetText(renderer);
	GetScale().PointToPixel(rect, 0.0f, 6.0f, 0.5f, 0.5f);
	if (font != nullptr) {
		SDL_RenderCopy(renderer, font, NULL, &rect);
		SDL_DestroyTexture(font);
	}
	else {
		std::cout << "font not loaded" << std::endl;
	}
}
