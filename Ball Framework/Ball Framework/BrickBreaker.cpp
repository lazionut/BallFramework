#include "BrickBreaker.h"

#define WIDTHUNITS 10
#define HEIGHTUNITS 13
#define BRICKROWS 7
#define BRICKPERROW 9
#define BRICKW 0.81f
#define BRICKH 0.35f
#define SPACING 0.25f
#define HEARTSIZE 0.25f
constexpr auto BRICKLIMIT_X = -WIDTHUNITS / 2 + 0.75f;
constexpr auto BRICKLIMIT_Y = HEIGHTUNITS / 2 - SPACING * 2;
constexpr auto LEFTLIMIT = -WIDTHUNITS / 2;
constexpr auto RIGHTLIMIT = WIDTHUNITS / 2;
constexpr auto UPPERLIMIT = HEIGHTUNITS / 2;
constexpr auto LOWERLIMIT = -HEIGHTUNITS / 2;

BrickBreaker::BrickBreaker(uint16_t width, uint16_t height, TTF_Font* font, uint32_t flags, uint16_t maxFPS)
	: Game("BrickBreaker", width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),
	m_ballImage{ nullptr }, m_heartImage{ nullptr }, m_pickUpImage{ nullptr }, m_font{ font },
	m_paddle(Vector2(0, -HEIGHTUNITS / 2 + 0.5f), 2.0f, 0.25f, Vector2::left, Vector2::right,
		SDLK_LEFT, SDLK_RIGHT, 5.0), m_bricks{ BRICKROWS }, m_score{ font },
	m_ball(Vector2(0, -HEIGHTUNITS / 2 + 1.0f), 0.5f, Vector2(0, 1), 4),
	m_heartCounter{ 3 }, m_isPickCreated{ false }, m_isPickActive{ true }
{

}

void BrickBreaker::Start()
{
	InitBricks();
	InitHearts();
	m_ballImage = LoadImage("../Assets/redball.png");
	m_heartImage = LoadImage("../Assets/redheart.png");
	if (m_ballImage == nullptr || m_heartImage == nullptr)
	{
		std::cout << "Could not load image\n";
		Stop();
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

void BrickBreaker::OnClose()
{
	SDL_DestroyTexture(m_ballImage);
	SDL_DestroyTexture(m_heartImage);
}

void BrickBreaker::ResetBall()
{

	//xBall = pow(-1, (rand() % 2));
	m_ball.SetDirection(0, 1);
	m_ball.SetPosition(0, 0);
}

void BrickBreaker::CreatePickUp(const Vector2& position)
{
	using Generator = PickUpGenerator::Actions;

	if (rand() % 100 > 80)
	{
		m_isPickCreated = true;

		switch (m_pickUpGenerator.GetPickUpType())
		{
		case Generator::SPEEDCHANGE:
			m_pickUp = m_pickUpGenerator.CreateSpeedPickUp();
			break;
		case Generator::PADDLESIZECHANGE:
			m_pickUp = m_pickUpGenerator.CreatePaddleSizeChangePickUp(m_paddle, 3);
			m_pickUp.SetDirection(m_paddle.GetPosition() + position);
			m_pickUp.StartMoving();
			break;
		case Generator::PADDLESPEEDCHANGE:
			m_pickUp = m_pickUpGenerator.CreatePaddleSpeedChangePickUp(m_paddle, 3);
			m_pickUp.SetDirection(m_paddle.GetPosition() + position);
			m_pickUp.StartMoving();
			break;
		case Generator::BALLSIZECHANGE:
			m_pickUp = m_pickUpGenerator.CreateBallSizeChangePickUp(m_ball, 1.25f);
			break;
		case Generator::BALLSPEEDCHANGE:
			m_pickUp = m_pickUpGenerator.CreateBallSpeedChangePickUp(m_ball, 4);
			break;
		case Generator::BONUSPOINTS:
			m_pickUp = m_pickUpGenerator.CreateBonusPointsPickUp(m_score, rand() % 5 + 1);
			break;
		case Generator::REMOVEPOINTS:
			m_pickUp = m_pickUpGenerator.CreateRemovePointsPickUp(m_score, rand() % 5 + 1);
			break;
		default:
			std::cout << "Could not create pickUp!\n";
			Stop();
			return;
		}

		m_isPickActive = true;
		if (rand() % 2 == 1)
		{
			m_pickUp.Set(position, Vector2(0.75f, 0.75f), Vector2(0, rand() % 2), 4.5f);
			m_pickUp.Move();
		}
		else
		{
			m_pickUp.SetDimension(Vector2(0.75f, 0.75f));
			m_pickUp.SetPosition(Vector2(0, 0));
		}
	}
	else
	{
		m_isPickActive = false;
		m_isPickCreated = false;
	}
}

void BrickBreaker::CheckCollision()
{

	CheckPaddleWallCollision();
	CheckBrickBreakerBallWallCollision();
	CheckBrickBreakerBallPaddleColision();
	CheckBallBricksColision();
}

bool BrickBreaker::CheckBrickBreakerBallWallCollision()
{
	const Vector2& ballPosition = m_ball.GetPosition();

	if (ballPosition.GetX() + m_ball.GetSize() / 2 > RIGHTLIMIT)
	{
		m_ball.GetPosition().SetX(RIGHTLIMIT - m_ball.GetSize() / 2);
		m_ball.SetDirection(-m_ball.GetDirection().GetX(), m_ball.GetDirection().GetY());
		return true;
	}
	if (ballPosition.GetX() - m_ball.GetSize() / 2 < LEFTLIMIT)
	{
		m_ball.SetPosition(LEFTLIMIT + m_ball.GetSize() / 2, m_ball.GetPosition().GetY());
		m_ball.SetDirection(-m_ball.GetDirection().GetX(), m_ball.GetDirection().GetY());
	}
	if (ballPosition.GetY() > BRICKLIMIT_Y)
	{
		m_ball.SetDirection(m_ball.GetDirection().GetX(), -m_ball.GetDirection().GetY());
		return true;
	}

	if (ballPosition.GetY() < LOWERLIMIT)
	{
		m_hearts.erase(m_hearts.begin());
		--m_heartCounter;
		if (m_heartCounter == 0)
		{
			playersStatistics.ReadStatistics("..\\Assets\\statisticsBB.txt");
			playersStatistics.UpdateStatistics("Player3", "..\\Assets\\statisticsBB.txt", false);
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "Better luck next time!", NULL);
			Stop();
		}
		ResetBall();
	}
	return false;
}

void BrickBreaker::CheckBallBricksColision()
{
	for (auto& row : m_bricks)
	{
		for (auto element = row.begin(); element < row.end(); ++element)
		{
			if (m_ball.CheckCollision(*element))
			{
				m_ball.ChangeDirection(*element);
				row.erase(element);
				if (m_isPickCreated == false)
					CreatePickUp(Vector2::zero);
				m_score.AddPoints(1);
				return;
			}
		}
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

void BrickBreaker::InitHearts()
{
	float ofset = 0.25;
	float x = LEFTLIMIT + 0.5;
	float y = LOWERLIMIT + 0.1;

	m_hearts.resize(m_heartCounter);

	for (int i = 0; i < m_heartCounter; i++)
	{
		Rectangle rect;
		m_hearts.push_back(rect);
		m_hearts[i].Set(Vector2(x, y), HEARTSIZE, HEARTSIZE);
		x = x + ofset + HEARTSIZE;
	}
	m_hearts.resize(m_heartCounter);
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
	RenderHearts(renderer);

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

void BrickBreaker::RenderHearts(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	const auto& scale = GetScale();
	for (const auto& iter : m_hearts)
	{
		scale.PointToPixel(rect, iter.GetPosition(), iter.GetWidth(), iter.GetHeight());
		SDL_RenderCopy(renderer, m_heartImage, NULL, &rect);
	}
}

void BrickBreaker::CheckPaddleWallCollision()
{
	if (m_paddle.GetPosition().GetX() < LEFTLIMIT + m_paddle.GetWidth() / 2)
	{
		m_paddle.SetPosition(LEFTLIMIT + m_paddle.GetWidth() / 2, m_paddle.GetPosition().GetY());
	}
	if (m_paddle.GetPosition().GetX() > RIGHTLIMIT - m_paddle.GetWidth() / 2)
	{
		m_paddle.SetPosition(RIGHTLIMIT - m_paddle.GetWidth() / 2, m_paddle.GetPosition().GetY());
	}
}

void BrickBreaker::CheckBrickBreakerBallPaddleColision()
{
	if (m_ball.CheckCollision(m_paddle))
	{
		if (m_ball.GetPosition().GetY() >= m_paddle.GetPosition().GetY() + m_paddle.GetHeight() / 2) //temporary solution to a bug
		{
			//m_ball.ChangeDirection(m_paddle);
			float difference = abs(m_ball.GetPosition().GetX() - m_paddle.GetPosition().GetX());
			m_ball.GetDirection().GetY() *= -1;

			//if (m_ball.GetDirection().GetX() >= 0) //prima versiune

			if (m_ball.GetPosition().GetX() >= m_paddle.GetPosition().GetX())
				//asta e a doua optiune de design in care mingea isi schimba dir 
				//pe axa x in functie de unde pica pe paleta
			{
				m_ball.GetDirection().SetX(difference);
			}
			else
				m_ball.GetDirection().SetX(-difference);
			m_ball.GetDirection().Normalize();
		}
		else
			m_ball.SetDirection(Vector2::down);
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