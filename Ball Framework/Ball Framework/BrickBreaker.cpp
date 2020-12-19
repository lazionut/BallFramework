#include "BrickBreaker.h"

#define WIDTHUNITS 10
#define HEIGHTUNITS 13
#define BRICKROWS 7
#define BRICKPERROW 9
#define BRICKW 0.81f
#define BRICKH 0.35f
#define SPACING 0.25f
constexpr auto BRICKLIMIT_X = -WIDTHUNITS / 2 + 0.75f;
constexpr auto BRICKLIMIT_Y = HEIGHTUNITS / 2 - SPACING * 2;
constexpr auto LEFTLIMIT = -WIDTHUNITS / 2;
constexpr auto RIGHTLIMIT = WIDTHUNITS / 2;
constexpr auto UPPERLIMIT = HEIGHTUNITS / 2;
constexpr auto LOWERLIMIT = -HEIGHTUNITS / 2;

BrickBreaker::BrickBreaker(uint16_t width, uint16_t height, TTF_Font* font, uint32_t flags, uint16_t maxFPS)
	: Game("BrickBreaker", width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),
	m_font{ font },
	m_paddle(Vector2(0, -HEIGHTUNITS / 2 + 0.5f), 2.0f, 0.25f, Vector2::left, Vector2::right,
		SDLK_LEFT, SDLK_RIGHT, 5.0), m_bricks{ BRICKROWS }, m_score{ font },
	m_ball(Vector2(0, -HEIGHTUNITS / 2 + 1.0f), 0.25f, Vector2(0, 1), 2.0f),
	m_heartCounter{ 3 }
{

}

void BrickBreaker::Start()
{
	InitBricks();
	m_ballImage = LoadImage("../Assets/redball.png");

	if (m_ballImage == nullptr)
	{
		std::cout << "Could not load ball image\n";
		Stop();
	}

	ResetBall();

	m_pickUp.SetStartAction(PickUpActions::SpeedUp);
	m_pickUp.InvokeAction();
}

void BrickBreaker::OnClose()
{
	SDL_DestroyTexture(m_ballImage);
}

void BrickBreaker::ResetBall()
{
	float xBall;
	//xBall = pow(-1, (rand() % 2));
	m_ball.SetDirection(0, 1);
	m_ball.SetPosition(0, 0);
}

void BrickBreaker::CheckCollision()
{
	if (m_paddle.GetPosition().GetX() < LEFTLIMIT + m_paddle.GetWidth() / 2)
	{
		m_paddle.SetPosition(LEFTLIMIT + m_paddle.GetWidth() / 2, m_paddle.GetPosition().GetY());
	}
	if (m_paddle.GetPosition().GetX() > RIGHTLIMIT - m_paddle.GetWidth() / 2)
	{
		m_paddle.SetPosition(RIGHTLIMIT - m_paddle.GetWidth() / 2, m_paddle.GetPosition().GetY());
	}

	CheckBrickBreakerBallWallCollision();

	if (m_ball.CheckCollision(m_paddle))
	{
		//m_ball.ChangeDirection(m_paddle);
		float difference = m_ball.GetPosition().GetX() - m_paddle.GetPosition().GetX() / 2;
		m_ball.GetDirection().GetY() *= -1;
		m_ball.GetDirection().SetX(difference);
		m_ball.GetDirection().Normalize();
	}

	for (auto& row : m_bricks)
	{
		for (auto element = row.begin(); element < row.end(); ++element)
		{
			if (m_ball.CheckCollision(*element)) //de lucrat aici
			{
				m_ball.ChangeDirection(*element);
				row.erase(element);
				m_score.AddPoints(1);
				return;
			}
		}
	}
}

void BrickBreaker::CheckBrickBreakerBallWallCollision()
{
	const Vector2& ballPosition = m_ball.GetPosition();

	if (ballPosition.GetX() + m_ball.GetSize() / 2 > RIGHTLIMIT || ballPosition.GetX() - m_ball.GetSize() / 2 < LEFTLIMIT)
	{
		m_ball.SetDirection(-m_ball.GetDirection().GetX(), m_ball.GetDirection().GetY());
	}

	if (ballPosition.GetY() > BRICKLIMIT_Y)
	{
		m_ball.SetDirection(m_ball.GetDirection().GetX(), -m_ball.GetDirection().GetY());
	}

	if (ballPosition.GetY() < LOWERLIMIT)
	{
		--m_heartCounter;
		if (m_heartCounter == 0)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "Better luck next time!", NULL);
			Stop();
		}
		ResetBall();
	}
}

void BrickBreaker::Update()
{
	m_paddle.Move();
	m_ball.Move();
	m_pickUp.ContinueAction();
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
			m_bricks[i][j].Set(Vector2(x, y), BRICKW, BRICKH);
			x = x + SPACING + BRICKW;
		}

		x = BRICKLIMIT_X;
		y -= offset;
	}
}

void BrickBreaker::KeyPressed(const SDL_Keycode& key)
{
	if (!m_paused)
	{
		m_paddle.KeyPressed(key);
	}
}

void BrickBreaker::KeyReleased(const SDL_Keycode& key)
{
	if (key == SDLK_p || key == SDLK_ESCAPE)
	{
		Pause();
	}
	else if (!m_paused) 
	{
		m_paddle.KeyReleased(key);
	}
}

void BrickBreaker::MousePressed(const SDL_MouseButtonEvent& mouse)
{
}

void BrickBreaker::MouseReleased(const SDL_MouseButtonEvent& mouse)
{
}

void BrickBreaker::Render(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	const auto& scale = GetScale();
	scale.PointToPixel(rect, m_paddle.GetPosition(), m_paddle.GetWidth(), m_paddle.GetHeight());
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
	RenderBricks(renderer);
	RenderScore(renderer);

	scale.PointToPixel(rect, m_ball.GetPosition(), m_ball.GetSize(), m_ball.GetSize());
	SDL_RenderCopy(renderer, m_ballImage, NULL, &rect);

}

void BrickBreaker::RenderBricks(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	const auto& scale = GetScale();

	for (const auto& iter1 : m_bricks)
	{
		for (const auto& iter2 : iter1)
		{
			scale.PointToPixel(rect, iter2.GetPosition(), iter2.GetWidth(), iter2.GetHeight());
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}

void BrickBreaker::RenderScore(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	SDL_Texture* fontTexture = m_score.GetText(renderer);
	if (m_score.GetScore() < 10) {
		GetScale().PointToPixel(rect, 0.0f, 6.1f, 0.5f, 0.9f);
	}
	else {
		GetScale().PointToPixel(rect, 0.0f, 6.1f, 1.0f, 0.9f);
	}
	if (m_font != nullptr)
	{
		SDL_RenderCopy(renderer, fontTexture, nullptr, &rect);
		SDL_DestroyTexture(fontTexture);
	}
	else
	{
		std::cout << "Font not loaded" << std::endl;
	}
}