#include "Pong.h"

#define WIDTHUNITS 20
#define HEIGHTUNITS 10
#define PADDLEWIDTH 3.0f
#define PADDLEHEIGHT 0.5f
#define HEIGHTPADDLESPACING 0.010f
#define PADDLESPEED 6.0f
#define BRICKCOLUMNS 4
#define BRICKSPERCOLUMN 4
#define BRICKWIDTH 0.81f
#define BRICKHEIGHT 0.35f

constexpr auto WIDTHPADDLESPACING1 = -WIDTHUNITS / 2 + 1;
constexpr auto WIDTHPADDLESPACING2 = WIDTHUNITS / 2 - 1;
constexpr auto UPPERLIMIT = HEIGHTUNITS / 2;
constexpr auto LOWERLIMIT = -HEIGHTUNITS / 2;
constexpr auto LEFTLIMIT = -WIDTHUNITS / 2;
constexpr auto RIGHTLIMIT = WIDTHUNITS / 2;

Pong::Pong(uint16_t width, uint16_t height, TTF_Font* font, uint32_t flags, uint16_t maxFPS)
	: Game("Pong", width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),

	m_pongPaddle1(Vector2(WIDTHPADDLESPACING1, 0), PADDLEHEIGHT, PADDLEWIDTH, Vector2::up, Vector2::down, SDLK_w, SDLK_s, PADDLESPEED),
	m_pongPaddle2(Vector2(WIDTHPADDLESPACING2, 0), PADDLEHEIGHT, PADDLEWIDTH, Vector2::up, Vector2::down, SDLK_UP, SDLK_DOWN, PADDLESPEED),
	m_bricks{ BRICKCOLUMNS }, m_ballImage{ nullptr }, m_pongBall{ Vector2::zero, 0.75f, Vector2(pow(-1, (rand() % 2)), 0), 5 },
	m_font{ font }, m_pongScore1{ font }, m_pongScore2{ font }
{
}

void Pong::Start()
{
	InitialiseBricks();

	m_ballImage = LoadImage("../Assets/ball.png");

	if (m_ballImage == nullptr)
	{
		std::cout << "Could not load the ball image!\n";
		Stop();
		return;
	}

	ResetBall();
}

void Pong::OnClose()
{
	SDL_DestroyTexture(m_ballImage);
}

void Pong::ResetBall()
{
	m_pongBall.SetDirection(pow(-1, (rand() % 2)), 0);
}

void Pong::CheckCollision()
{
	float paddleTop1 = m_pongPaddle1.GetPosition().GetY();
	float paddleTop2 = m_pongPaddle2.GetPosition().GetY();

	const Vector2& ballPosition = m_pongBall.GetPosition();

	//check ball wall collision
	if (ballPosition.GetY() + m_pongBall.GetSize() / 2 > UPPERLIMIT ||
		ballPosition.GetY() - m_pongBall.GetSize() / 2 < LOWERLIMIT)
	{
		//m_pongBall.SetDirection(m_pongBall.GetDirection().GetX(), -m_pongBall.GetDirection().GetY());
		//m_pongBall.GetDirection().SetY(-m_pongBall.GetDirection().GetY());
		m_pongBall.GetDirection().GetY() *= -1;
	}

	//check paddle1 wall limits
	if (paddleTop1 < LOWERLIMIT + m_pongPaddle1.GetHeight() / 2)
	{
		m_pongPaddle1.SetPosition(WIDTHPADDLESPACING1, LOWERLIMIT + m_pongPaddle1.GetHeight() / 2 + HEIGHTPADDLESPACING);
	}
	if (paddleTop1 > UPPERLIMIT - m_pongPaddle1.GetHeight() / 2)
	{
		m_pongPaddle1.SetPosition(WIDTHPADDLESPACING1, UPPERLIMIT - m_pongPaddle1.GetHeight() / 2 - HEIGHTPADDLESPACING);
	}

	//check paddle2 wall limits
	if (paddleTop2 < LOWERLIMIT + m_pongPaddle2.GetHeight() / 2)
	{
		m_pongPaddle2.SetPosition(WIDTHPADDLESPACING2, LOWERLIMIT + m_pongPaddle2.GetHeight() / 2 + HEIGHTPADDLESPACING);
	}
	if (paddleTop2 > UPPERLIMIT - m_pongPaddle2.GetHeight() / 2)
	{
		m_pongPaddle2.SetPosition(WIDTHPADDLESPACING2, UPPERLIMIT - m_pongPaddle2.GetHeight() / 2 - HEIGHTPADDLESPACING);
	}

	//check ball collision with paddles
	if (m_pongBall.GetDirection().GetX() < 0 && m_pongBall.CheckCollision(m_pongPaddle1))
	{
		//m_pongBall.SetDirection(m_pongBall.GetDirection().GetX() * -1, m_pongBall.GetDirection().GetY());
		//m_pongBall.GetDirection().SetX(-m_pongBall.GetDirection().GetX());

		float difference = m_pongBall.GetPosition().GetY() - m_pongPaddle1.GetPosition().GetY();
		m_pongBall.GetDirection().GetX() *= -1;
		m_pongBall.GetDirection().SetY(difference);
		m_pongBall.AddSpeed(0.25f);

	}
	if (m_pongBall.GetDirection().GetX() > 0 && m_pongBall.CheckCollision(m_pongPaddle2))
	{
		//m_pongBall.SetDirection(m_pongBall.GetDirection().GetX() * -1, m_pongBall.GetDirection().GetY());
		//m_pongBall.GetDirection().SetX(-m_pongBall.GetDirection().GetX());

		float difference = m_pongBall.GetPosition().GetY() - m_pongPaddle2.GetPosition().GetY();
		m_pongBall.GetDirection().GetX() *= -1;
		m_pongBall.GetDirection().SetY(difference);
		m_pongBall.AddSpeed(0.25f);
	}

	//check if a player lost the ball
	if (m_pongBall.GetPosition().GetX() < LEFTLIMIT)
	{
		m_pongScore1.AddPoints(1);
		m_pongBall.SetPosition(0, 0);
		m_pongBall.SetDirection(-1, 0);
		m_pongBall.SetSpeed(5);
	}
	if (m_pongBall.GetPosition().GetX() > RIGHTLIMIT)
	{
		m_pongScore2.AddPoints(1);
		m_pongBall.SetPosition(0, 0);
		m_pongBall.SetDirection(1, 0);
		m_pongBall.SetSpeed(5);
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

void Pong::MousePressed(const SDL_MouseButtonEvent& mouse)
{
}

void Pong::MouseReleased(const SDL_MouseButtonEvent& mouse)
{
}

void Pong::Render(SDL_Renderer* renderer)
{
	SDL_Rect aux;
	const auto& scale = GetScale();

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	scale.PointToPixel(aux, m_pongPaddle1.GetPosition(), m_pongPaddle1.GetWidth(), m_pongPaddle1.GetHeight());
	SDL_RenderFillRect(renderer, &aux);
	scale.PointToPixel(aux, m_pongPaddle2.GetPosition(), m_pongPaddle2.GetWidth(), m_pongPaddle2.GetHeight());
	SDL_RenderFillRect(renderer, &aux);

	uint16_t screenHeight = scale.GetScreenHeight();
	uint16_t screenCenter = scale.GetScreenWidth() / 2;
	for (int index = 0; index < screenHeight; index += 3)
	{
		SDL_RenderDrawPoint(renderer, screenCenter, index);
	}

	scale.PointToPixel(aux, m_pongBall.GetPosition(), m_pongBall.GetSize(), m_pongBall.GetSize());
	SDL_RenderCopy(renderer, m_ballImage, nullptr, &aux);

	RenderBricks(renderer);
	RenderPlayersScore(renderer);
}

void Pong::InitialiseBricks()
{
	float x = -1.5f, y = -3;
	for (int row = 0; row < BRICKCOLUMNS; ++row)
	{
		m_bricks[row].resize(BRICKSPERCOLUMN);
		for (int column = 0; column < BRICKSPERCOLUMN; ++column)
		{
			m_bricks[row][column].Set(Vector2(x, y), BRICKWIDTH, BRICKHEIGHT);
			y+=2;
		}
		++x;
		y = -3;
	}
}

void Pong::RenderBricks(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	const auto& scale = GetScale();
	for (const auto& rowIterator : m_bricks)
		for (const auto& columnIterator : rowIterator)
		{
			scale.PointToPixel(rect, columnIterator.GetPosition(), columnIterator.GetHeight(), columnIterator.GetWidth());
			SDL_RenderFillRect(renderer, &rect);
		}
}

void Pong::RenderPlayersScore(SDL_Renderer* renderer)
{
	SDL_Rect aux1, aux2;
	const auto& scale = GetScale();

	SDL_Texture* scoreTexture1 = m_pongScore1.GetText(renderer);
	scale.PointToPixel(aux1, 2, 4, 0.5f, 0.5f);

	SDL_Texture* scoreTexture2 = m_pongScore2.GetText(renderer);
	scale.PointToPixel(aux2, -2, 4, 0.5f, 0.5f);

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