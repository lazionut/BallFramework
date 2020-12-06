#include "Pong.h"

#define WIDTHUNITS 20
#define HEIGHTUNITS 10
#define EMPTYSPACE 1
#define PADDLEWIDTH 3.0f
#define PADDLEHEIGHT 0.5f
constexpr auto WIDTHPADDLESPACING1 = (WIDTHUNITS * -1) / 2 + 1;
constexpr auto WIDTHPADDLESPACING2 = WIDTHUNITS / 2 - 1;
#define HEIGHTPADDLESPACING 0.010f

Pong::Pong(uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
	: Game("Pong", width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),
	m_pongPaddle1(Vector2(WIDTHPADDLESPACING1, 0), PADDLEHEIGHT, PADDLEWIDTH, Vector2::up, Vector2::down, SDLK_w, SDLK_s, 4),
	m_pongPaddle2(Vector2(WIDTHPADDLESPACING2, 0), PADDLEHEIGHT, PADDLEWIDTH, Vector2::up, Vector2::down, SDLK_UP, SDLK_DOWN, 4),
	m_ballImage{ nullptr }, m_pongBall{ Vector2(0,0), 0.75f, Vector2(1,0), 3 }
{

}

void Pong::Start()
{
	m_ballImage = LoadImage("ball.png");
	if (m_ballImage == nullptr)
		Stop();
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
		m_pongBall.SetPosition(0, 0);
		m_pongBall.SetDirection(-1, 0);
		m_pongBall.SetSpeed(3);
	}

	if (m_pongBall.GetPosition().GetX() > 10)
	{
		m_pongScore2.AddPoints(1);
		m_pongBall.SetPosition(0, 0);
		m_pongBall.SetDirection(1, 0);
		m_pongBall.SetSpeed(3);
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

void Pong::Render(SDL_Renderer* renderer)
{
	SDL_Rect aux;
	const auto& scale = GetScale();
	scale.PointToPixel(aux, m_pongPaddle1.GetPosition(), m_pongPaddle1.GetWidth(), m_pongPaddle1.GetHeight());
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &aux);
	scale.PointToPixel(aux, m_pongPaddle2.GetPosition(), m_pongPaddle2.GetWidth(), m_pongPaddle2.GetHeight());
	SDL_RenderFillRect(renderer, &aux);
	for (int index = 0; index < scale.GetScreenHeight(); index += 10)
		SDL_RenderDrawPoint(renderer, scale.GetScreenWidth() / 2, index);
	scale.PointToPixel(aux, m_pongBall.GetPosition(), m_pongBall.GetSize(), m_pongBall.GetSize());
	SDL_RenderCopy(renderer, m_ballImage, NULL, &aux);
	RenderPlayersScore(renderer);
}

void Pong::RenderPlayersScore(SDL_Renderer* renderer)
{
	SDL_Rect aux1, aux2;
	const auto& scale = GetScale();
	SDL_Texture* scoreTexture1 = m_pongScore1.GetText(renderer);
	scale.PointToPixel(aux1, 2, 3, 0.5f, 0.5f);
	SDL_Texture* scoreTexture2 = m_pongScore2.GetText(renderer);
	scale.PointToPixel(aux2, -2, 3, 0.5f, 0.5f);
	if (scoreTexture1 != nullptr && scoreTexture2 != nullptr)
	{
		SDL_RenderCopy(renderer, scoreTexture1, nullptr, &aux1);
		SDL_RenderCopy(renderer, scoreTexture2, nullptr, &aux2);
		SDL_DestroyTexture(scoreTexture1);
		SDL_DestroyTexture(scoreTexture2);
	}
	else
	{
		std::cout << "Font was not loaded!" << std::endl;
	}
}