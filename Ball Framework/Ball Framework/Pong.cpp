#include "Pong.h"
#include "ScreenScale.h"
#include <SDL_ttf.h> 

#define WIDTHUNITS 20
#define HEIGHTUNITS 10
#define EMPTYSPACE 1
#define PADDLEWIDTH 3.0f
#define PADDLEHEIGHT 0.5f
#define BALLSIZE 0.75f
constexpr auto WIDTHPADDLESPACING1 = (WIDTHUNITS * -1) / 2 + 1;
constexpr auto WIDTHPADDLESPACING2 = WIDTHUNITS / 2 - 1;
#define HEIGHTPADDLESPACING 0.010f

Pong::Pong(int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
	: Game("Pong", x, y, width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),
	m_pongPaddle1(Vector2(WIDTHPADDLESPACING1, 0), PADDLEHEIGHT, PADDLEWIDTH, Vector2::up, Vector2::down, SDLK_w, SDLK_s, 4),
	m_pongPaddle2(Vector2(WIDTHPADDLESPACING2, 0), PADDLEHEIGHT, PADDLEWIDTH, Vector2::up, Vector2::down, SDLK_UP, SDLK_DOWN, 4)
{

}

Pong::Pong(uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
	: Game("Pong", width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),
	m_pongPaddle1(Vector2(WIDTHPADDLESPACING1, 0), PADDLEHEIGHT, PADDLEWIDTH, Vector2::up, Vector2::down, SDLK_w, SDLK_s, 4),
	m_pongPaddle2(Vector2(WIDTHPADDLESPACING2, 0), PADDLEHEIGHT, PADDLEWIDTH, Vector2::up, Vector2::down, SDLK_UP, SDLK_DOWN, 4)
{

}

void Pong::Start()
{
	m_ballImage = LoadImage("ball.png");
	if (m_ballImage == nullptr)
		Stop();
	m_pongBall.SetPosition(m_pongBall.GetPosition().GetX(), m_pongBall.GetPosition().GetY());
	m_pongBall.SetSize(BALLSIZE);
	m_pongBall.SetDirection(1, 0);
	m_pongBall.SetSpeed(3);
}

void Pong::OnClose()
{
	SDL_DestroyTexture(m_ballImage);
}

void Pong::CheckCollision()
{
	float paddleTop1 = m_pongPaddle1.GetPosition().GetY();
	float paddleTop2 = m_pongPaddle2.GetPosition().GetY();

	if (paddleTop1 < (HEIGHTUNITS * -1) / 2 + m_pongPaddle1.GetHeight() / 2)
		m_pongPaddle1.SetPosition(WIDTHPADDLESPACING1, (HEIGHTUNITS * -1) / 2 + m_pongPaddle1.GetHeight() / 2 + HEIGHTPADDLESPACING);
	if (paddleTop1 > HEIGHTUNITS / 2 - m_pongPaddle1.GetHeight() / 2)
		m_pongPaddle1.SetPosition(WIDTHPADDLESPACING1, HEIGHTUNITS / 2 - m_pongPaddle1.GetHeight() / 2 - HEIGHTPADDLESPACING);
	if (paddleTop2 < (HEIGHTUNITS * -1) / 2 + m_pongPaddle2.GetHeight() / 2)
		m_pongPaddle2.SetPosition(WIDTHPADDLESPACING2, (HEIGHTUNITS * -1) / 2 + m_pongPaddle2.GetHeight() / 2 + HEIGHTPADDLESPACING);
	if (paddleTop2 > HEIGHTUNITS / 2 - m_pongPaddle2.GetHeight() / 2)
		m_pongPaddle2.SetPosition(WIDTHPADDLESPACING2, HEIGHTUNITS / 2 - m_pongPaddle2.GetHeight() / 2 - HEIGHTPADDLESPACING);

	if (m_pongBall.CheckCollision(m_pongPaddle1))
	{
		m_pongBall.SetDirection(m_pongBall.GetDirection().GetX() * -1, m_pongBall.GetDirection().GetY());
		m_pongBall.SetSpeed(m_pongBall.GetSpeed() + 0.25f);
	}

	if (m_pongBall.CheckCollision(m_pongPaddle2))
	{
		m_pongBall.SetDirection(m_pongBall.GetDirection().GetX() * -1, m_pongBall.GetDirection().GetY());
		m_pongBall.SetSpeed(m_pongBall.GetSpeed() + 0.25f);
	}

	if (m_pongBall.GetPosition().GetX() < -10)
	{
		m_pongScore1.AddPoints(1);
	}

	if (m_pongBall.GetPosition().GetX() > 10)
	{
		m_pongScore2.AddPoints(1);
	}
}

void Pong::Update()
{
	m_pongPaddle1.Move();
	m_pongPaddle2.Move();
	m_pongBall.Move();
}

void Pong::KeyPressed(const SDL_Keycode& key)
{
	m_pongPaddle1.KeyPressed(key);
	m_pongPaddle2.KeyPressed(key);
}

void Pong::KeyReleased(const SDL_Keycode& key)
{
	m_pongPaddle1.KeyReleased(key);
	m_pongPaddle2.KeyReleased(key);
}

void Pong::PlayerScore(SDL_Renderer* renderer, TTF_Font* font)
{

}

void Pong::Render(SDL_Renderer* renderer)
{
	SDL_Rect aux;
	GetScale().PointToPixel(aux, m_pongPaddle1.GetPosition(), m_pongPaddle1.GetWidth(), m_pongPaddle1.GetHeight());
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &aux);
	GetScale().PointToPixel(aux, m_pongPaddle2.GetPosition(), m_pongPaddle2.GetWidth(), m_pongPaddle2.GetHeight());
	SDL_RenderFillRect(renderer, &aux);
	for (int index = 0; index < GetScale().GetScreenHeight(); ++index)
		if (index % 2)
			SDL_RenderDrawPoint(renderer, GetScale().GetScreenWidth() / 2, index);
	GetScale().PointToPixel(aux, m_pongBall.GetPosition(), m_pongBall.GetSize(), m_pongBall.GetSize());
	SDL_RenderCopy(renderer, m_ballImage, NULL, &aux);
}