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
#define BRICKLIMIT_X -1.5f
#define BRICKLIMIT_Y -3
#define BRICKSPACING 2

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
	m_bricks{ BRICKCOLUMNS }, m_bricksNumber{ 0 }, m_ballImage{ nullptr }, m_pickUpImage{ nullptr }, m_pongBall{ Vector2::zero, 0.75f, Vector2(pow(-1, (rand() % 2)), 0), 10 },
	m_font{ font }, m_pongScore1{ font }, m_pongScore2{ font }, m_isPickCreated{ false }, m_isPickActive{ true },
	m_pauseButton{ Vector2(-WIDTHUNITS / 2 + 0.38f, HEIGHTUNITS / 2 - 0.5f), 0.7f, 0.7f, black, white, "||", m_font}, m_paused{ false }
{
	m_lastTimeScale = Time::GetTimeScale();
}

void Pong::Start()
{
	InitializeBricks();

	m_ballImage = LoadImage("../Assets/ball.png");

	if (m_ballImage == nullptr)
	{
		std::cout << "Could not load the ball image!\n";
		Stop();
		return;
	}

	ResetBall();
	m_pickUpImage = LoadImage("../Assets/star.png");

	if (m_pickUpImage == nullptr)
	{
		std::cout << "could not load pickup texture\n";
		Stop();
		return;
	}

	CreatePickUp(Vector2::zero);
}

void Pong::OnClose()
{
	SDL_DestroyTexture(m_ballImage);
	SDL_DestroyTexture(m_pickUpImage);
	Time::SetTimeScale(m_lastTimeScale);
}

void Pong::ResetBall()
{
	m_pongBall.SetDirection(pow(-1, (rand() % 2)), 0);
}

void Pong::CreatePickUp(const Vector2& position)
{
	using Generator = PickUpGenerator::Actions;

	if (rand() % 100 > 80)
	{
		m_isPickCreated = true;
		auto random = rand() % 2;
		auto difference = 0.0f;

		switch (m_pickUpGenerator.GetPickUpType())
		{
		case Generator::SPEEDCHANGE:
			m_pickUp = m_pickUpGenerator.CreateSpeedPickUp();
			m_pickUp.StartMoving();
			break;
		case Generator::PADDLESIZECHANGE:
			difference = 3;
			if (random)
			{
				m_pickUp = m_pickUpGenerator.CreatePaddleSizeChangePickUp(m_pongPaddle1, difference);
				m_pickUp.SetDirection(m_pongPaddle1.GetPosition() - position);
			}
			else
			{
				m_pickUp = m_pickUpGenerator.CreatePaddleSizeChangePickUp(m_pongPaddle2, difference);
				m_pickUp.SetDirection(m_pongPaddle1.GetPosition() - position);
			}
			m_pickUp.StartMoving();
			break;
		case Generator::PADDLESPEEDCHANGE:
			difference = 3;
			if (random)
			{
				m_pickUp = m_pickUpGenerator.CreatePaddleSpeedChangePickUp(m_pongPaddle1, difference);
				m_pickUp.SetDirection(m_pongPaddle1.GetPosition() - position);
			}
			else
			{
				m_pickUp = m_pickUpGenerator.CreatePaddleSpeedChangePickUp(m_pongPaddle2, difference);
				m_pickUp.SetDirection(m_pongPaddle1.GetPosition() - position);
			}
			m_pickUp.StartMoving();
			break;
		case Generator::BALLSIZECHANGE:
			m_pickUp = m_pickUpGenerator.CreateBallSizeChangePickUp(m_pongBall, 2);
			break;
		case Generator::BALLSPEEDCHANGE:
			m_pickUp = m_pickUpGenerator.CreateBallSpeedChangePickUp(m_pongBall, 2);
			break;
		case Generator::BONUSPOINTS:
			m_isPickActive = false;
			break;
		case Generator::REMOVEPOINTS:
			m_isPickActive = false;
			break;
		default:
			m_isPickCreated = false;
			return;
		}

		m_isPickActive = true;
		m_pickUp.Set(position, Vector2(0.75f, 0.75f), Vector2(rand() % 3 - 1, 0), 4.5f);
	}
	else
	{
		m_isPickActive = false;
		m_isPickCreated = false;
	}
}

void Pong::RenderButton(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	const auto& scale = GetScale();
	SDL_Texture* fontTexture;

	scale.PointToPixel(rect, m_pauseButton.GetPosition(), m_pauseButton.GetWidth(), m_pauseButton.GetHeight());
	SDL_SetRenderDrawColor(renderer, m_pauseButton.GetBackColor().r, m_pauseButton.GetBackColor().g,
		m_pauseButton.GetBackColor().b, m_pauseButton.GetBackColor().a);
	SDL_RenderFillRect(renderer, &rect);
	m_pauseButton.SetRect(rect);

	fontTexture = m_pauseButton.GetText(renderer);
	GetScale().PointToPixel(rect, m_pauseButton.GetPosition().GetX(), m_pauseButton.GetPosition().GetY(),
		m_pauseButton.GetWidth() - 0.2f, m_pauseButton.GetHeight());
	if (fontTexture != nullptr)
	{
		SDL_RenderCopy(renderer, fontTexture, nullptr, &rect);
		//SDL_DestroyTexture(fontTexture);
	}
}

void Pong::CheckCollision()
{
	CheckBallWallCollision();
	CheckPaddleWallCollision();
	CheckBallPaddleCollision();
	CheckBallBrickCollision();
	CheckPickUpCollision();
	CheckScoreCondition();
}

void Pong::Update()
{
	m_pongPaddle1.Move();
	m_pongPaddle2.Move();
	m_pongBall.Move();

	if (m_pickUp.IsActionActive())
	{
		m_pickUp.ContinueAction();
	}

	if (m_pickUp.IsMoving())
	{
		m_pickUp.Move();
	}
}

void Pong::KeyPressed(const SDL_Keycode& key)
{
	if (!m_paused)
	{
		m_pongPaddle1.KeyPressed(key);
		m_pongPaddle2.KeyPressed(key);
	}
}

void Pong::KeyReleased(const SDL_Keycode& key)
{
	if (key == SDLK_p || key == SDLK_ESCAPE)
	{
		m_pauseButton.ChangeFontColor(m_renderer);
		Repaint();
		Pause();
	}
	else if (!m_paused)
	{
		m_pongPaddle1.KeyReleased(key);
		m_pongPaddle2.KeyReleased(key);
	}
}

void Pong::MousePressed(const SDL_MouseButtonEvent& mouse)
{
	IsInBounds(mouse.x, mouse.y);
}

void Pong::MouseReleased(const SDL_MouseButtonEvent& mouse)
{
	if (IsInBounds(mouse.x, mouse.y) == 1) {
		KeyReleased(SDLK_p);
	};
}

int Pong::IsInBounds(Sint32 x, Sint32 y)
{
	if (x > m_pauseButton.GetRect().x &&
		x < m_pauseButton.GetRect().x + m_pauseButton.GetRect().w
		&& y > m_pauseButton.GetRect().y &&
		y < m_pauseButton.GetRect().y + m_pauseButton.GetRect().h) {
		m_pauseButton.ChangeFontColor(m_renderer);
		return 1;
	}
	return -1;
}

void Pong::Render(SDL_Renderer* renderer)
{
	m_renderer = renderer;
	SDL_Rect aux;
	const auto& scale = GetScale();

	SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
	scale.PointToPixel(aux, m_pongPaddle1.GetPosition(), m_pongPaddle1.GetWidth(), m_pongPaddle1.GetHeight());
	SDL_RenderFillRect(m_renderer, &aux);
	scale.PointToPixel(aux, m_pongPaddle2.GetPosition(), m_pongPaddle2.GetWidth(), m_pongPaddle2.GetHeight());
	SDL_RenderFillRect(m_renderer, &aux);

	uint16_t screenHeight = scale.GetScreenHeight();
	uint16_t screenCenter = scale.GetScreenWidth() / 2;
	for (int index = 0; index < screenHeight; index += 3)
	{
		SDL_RenderDrawPoint(m_renderer, screenCenter, index);
	}

	scale.PointToPixel(aux, m_pongBall.GetPosition(), m_pongBall.GetSize(), m_pongBall.GetSize());
	SDL_RenderCopy(m_renderer, m_ballImage, nullptr, &aux);

	RenderBricks(m_renderer);
	RenderPlayersScore(m_renderer);
	RenderButton(m_renderer);

	if (m_isPickActive)
	{
		scale.PointToPixel(aux, m_pickUp.GetPosition(), m_pickUp.GetDimension());
		SDL_RenderCopy(m_renderer, m_pickUpImage, nullptr, &aux);
	}
}

void Pong::CheckBallWallCollision()
{
	if (m_pongBall.GetPosition().GetY() + m_pongBall.GetSize() / 2 > UPPERLIMIT)
	{
		//m_pongBall.SetDirection(m_pongBall.GetDirection().GetX(), -m_pongBall.GetDirection().GetY());
		//m_pongBall.GetDirection().SetY(-m_pongBall.GetDirection().GetY());

		m_pongBall.GetPosition().SetY(UPPERLIMIT - m_pongBall.GetSize() / 2);
		m_pongBall.GetDirection().GetY() *= -1;
	}
	else if (m_pongBall.GetPosition().GetY() - m_pongBall.GetSize() / 2 < LOWERLIMIT)
	{
		m_pongBall.GetPosition().SetY(LOWERLIMIT + m_pongBall.GetSize() / 2);
		m_pongBall.GetDirection().GetY() *= -1;
	}
}

void Pong::CheckPaddleWallCollision()
{
	if (m_pongPaddle1.GetPosition().GetY() < LOWERLIMIT + m_pongPaddle1.GetHeight() / 2)
	{
		m_pongPaddle1.SetPosition(WIDTHPADDLESPACING1, LOWERLIMIT + m_pongPaddle1.GetHeight() / 2 + HEIGHTPADDLESPACING);
	}
	else if (m_pongPaddle1.GetPosition().GetY() > UPPERLIMIT - m_pongPaddle1.GetHeight() / 2)
	{
		m_pongPaddle1.SetPosition(WIDTHPADDLESPACING1, UPPERLIMIT - m_pongPaddle1.GetHeight() / 2 - HEIGHTPADDLESPACING);
	}
	if (m_pongPaddle2.GetPosition().GetY() < LOWERLIMIT + m_pongPaddle2.GetHeight() / 2)
	{
		m_pongPaddle2.SetPosition(WIDTHPADDLESPACING2, LOWERLIMIT + m_pongPaddle2.GetHeight() / 2 + HEIGHTPADDLESPACING);
	}
	else if (m_pongPaddle2.GetPosition().GetY() > UPPERLIMIT - m_pongPaddle2.GetHeight() / 2)
	{
		m_pongPaddle2.SetPosition(WIDTHPADDLESPACING2, UPPERLIMIT - m_pongPaddle2.GetHeight() / 2 - HEIGHTPADDLESPACING);
	}
}

void Pong::CheckBallPaddleCollision()
{
	if (m_pongBall.CheckCollision(m_pongPaddle1))
	{
		//m_pongBall.SetDirection(m_pongBall.GetDirection().GetX() * -1, m_pongBall.GetDirection().GetY());
		//m_pongBall.GetDirection().SetX(-m_pongBall.GetDirection().GetX());

		float difference = m_pongBall.GetPosition().GetY() - m_pongPaddle1.GetPosition().GetY() / 2;
		m_pongBall.GetDirection().GetX() *= -1;
		m_pongBall.GetDirection().SetY(difference);
		m_pongBall.AddSpeed(0.25f);
		m_pongBall.GetDirection().Normalize();
	}
	else if (m_pongBall.CheckCollision(m_pongPaddle2))
	{
		//m_pongBall.SetDirection(m_pongBall.GetDirection().GetX() * -1, m_pongBall.GetDirection().GetY());
		//m_pongBall.GetDirection().SetX(-m_pongBall.GetDirection().GetX());

		float difference = m_pongBall.GetPosition().GetY() - m_pongPaddle2.GetPosition().GetY() / 2;
		m_pongBall.GetDirection().GetX() *= -1;
		m_pongBall.GetDirection().SetY(difference);
		m_pongBall.AddSpeed(0.25f);
		m_pongBall.GetDirection().Normalize();
	}
}

void Pong::CheckBallBrickCollision()
{
	for (auto& row : m_bricks)
		for (auto element = row.begin(); element < row.end(); ++element)
			if (m_pongBall.CheckCollision(*element))
			{
				if (m_isPickCreated == false)
					CreatePickUp(element->GetPosition());
				m_pongBall.ChangeDirection(*element);
				m_pongBall.GetDirection().Normalize();
				row.erase(element);

				--m_bricksNumber;

				if (m_bricksNumber < 1)
				{
					m_bricks.resize(BRICKCOLUMNS);
					InitializeBricks();
				}
				return;
			}
}

void Pong::CheckPickUpCollision()
{
	float ballSize = m_pongBall.GetSize() / 2;
	float pickUpSize = m_pickUp.GetDimension().GetX() / 2;

	if (m_isPickActive &&
		(m_pickUp.GetPosition() - m_pongBall.GetPosition()).GetSquareLength() < ballSize * ballSize + pickUpSize * pickUpSize)
	{
		std::cout << "pickUp collision\n";
		m_pickUp.InvokeAction(10.0f);
		m_isPickActive = false;
	}
}

void Pong::CheckScoreCondition()
{
	if (m_pongBall.GetPosition().GetX() < LEFTLIMIT)
	{
		m_pongScore1.AddPoints(1);
		if (m_pongScore1.GetScore() == 5)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "Player2 won!", NULL);
			Stop();
		}
		m_pongBall.SetPosition(0, 0);
		m_pongBall.SetDirection(-1, 0);
		m_pongBall.SetSpeed(10);
	}
	else if (m_pongBall.GetPosition().GetX() > RIGHTLIMIT)
	{
		m_pongScore2.AddPoints(1);
		if (m_pongScore2.GetScore() == 5)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "Player1 won!", NULL);
			Stop();
		}
		m_pongBall.SetPosition(0, 0);
		m_pongBall.SetDirection(1, 0);
		m_pongBall.SetSpeed(10);
	}
}

void Pong::InitializeBricks()
{
	float x = BRICKLIMIT_X, y = BRICKLIMIT_Y;

	for (auto&& row : m_bricks)
	{
		row.resize(BRICKSPERCOLUMN);

		for (auto&& elem : row)
		{
			elem.Set(Vector2(x, y), BRICKWIDTH, BRICKHEIGHT);
			y += BRICKSPACING;
		}

		++x;
		y = BRICKLIMIT_Y;
	}

	m_bricksNumber = BRICKCOLUMNS * BRICKSPERCOLUMN;
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

void Pong::Pause()
{
	if (!m_paused) {
		m_lastTimeScale = Time::GetTimeScale();
		Time::SetTimeScale(0);
		m_paused = true;
	}
	else {
		Time::SetTimeScale(m_lastTimeScale);
		m_paused = false;
	}
}