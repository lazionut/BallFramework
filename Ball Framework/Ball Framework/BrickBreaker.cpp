#include "BrickBreaker.h"

namespace BallFramework
{

#pragma region CONSTANTS
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

	//pickUp constants
#define PICKUPSPAWNCHANCE 20
#define ACTIONTIME 2.0f
#define PICKUPSIZECHANGE 0.25f
#define PICKUPSPEEDCHANGE 2.0f

#define PADDLESIZEDIFFERENCE 1.0f
#define PADDLESPEEDDIFFERENCE 3.0f

#define BALLSIZEDIFFERENCE 1.25f
#define BALLSPEEDDIFFERENCE 4.0f

#define MAXSCOREDIFFERENCE 5

#pragma endregion

	BrickBreaker::BrickBreaker(uint16_t width, uint16_t height, TTF_Font* font, uint32_t flags, uint16_t maxFPS)
		: Game("BrickBreaker", width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),

		m_renderer{ nullptr },
		m_paddle(Vector2(0, LOWERLIMIT + 0.5f), 2.0f, 0.25f, Vector2::left, Vector2::right, SDLK_LEFT, SDLK_RIGHT, 5.0),
		m_ball(Vector2(0, LOWERLIMIT + 1.0f), 0.5f, Vector2(0, 1), 4.5f), m_ballImage{ nullptr },
		m_bricks{ BRICKROWS },
		m_pickUpImage{ nullptr }, m_isPickCreated{ false }, m_isPickActive{ false },
		m_heartImage{ nullptr }, m_heartCounter{ 3 },
		m_score{ font },
		m_buttonFont{ font }, m_pauseButton{ Vector2(LEFTLIMIT + 0.5f, UPPERLIMIT + 0.1f), 0.7f, 0.7f, black, white, "||" },
		m_isPaused{ false },
		m_playersStatistics{ "..\\Assets\\statisticsBB.txt" }
	{
		m_lastTimeScale = Time::GetTimeScale();
	}

	void BrickBreaker::Start()
	{
		InitializeBricks();
		InitializeHearts();

		m_ballImage = LoadGameImage(Paths::ReturnObjectPath("redBall"));
		m_heartImage = LoadGameImage(Paths::ReturnObjectPath("redHeart"));
		m_pauseButton.SetText(MakeText(m_pauseButton.GetButtonText(), m_pauseButton.GetFontColor(), m_buttonFont));

		if (m_ballImage == nullptr)
		{
			LOGGING_ERROR("BrickBreaker ball image not found!");
			Stop();
			return;
		}

		if (m_heartImage == nullptr)
		{
			LOGGING_ERROR("BrickBreaker heart image not found!");
			Stop();
			return;
		}

		ResetBall();

		m_pickUpImage = LoadGameImage(Paths::ReturnObjectPath("star"));
		if (m_pickUpImage == nullptr)
		{
			LOGGING_ERROR("BrickBreaker pick-up image not found!");
			Stop();
			return;
		}

		m_pickUpGenerator.SetDefaultProperties(Vector2::right, PICKUPSIZECHANGE, PICKUPSPEEDCHANGE, ACTIONTIME);
	}

	void BrickBreaker::ResetBall()
	{
		m_ball.SetDirection(0, 1);
		m_ball.SetPosition(0, 0);
	}

	void BrickBreaker::Update()
	{
		m_paddle.Move();
		m_ball.Move();

		if (m_isPickCreated)
		{
			if (m_pickUp.IsActionActive())
			{
				if (m_pickUp.ContinueAction())
				{
					m_isPickCreated = false;
					return;
				}
			}

			if (m_pickUp.IsMoving())
			{
				m_pickUp.Move();
			}
		}
	}

	void BrickBreaker::OnClose()
	{
		SDL_DestroyTexture(m_ballImage);
		SDL_DestroyTexture(m_heartImage);
		Time::SetTimeScale(m_lastTimeScale);
	}

#pragma region Collision Methods

	void BrickBreaker::CheckCollision()
	{
		CheckPaddleWallCollision();
		CheckBallWallCollision();
		CheckBallPaddleCollision();
		CheckBallBrickCollision();

		if (m_isPickActive)
		{
			if (m_pickUp.IsMoving())
			{
				if (m_pickUp.CheckCollision(m_paddle))
				{
					m_pickUp.InvokeAction();
					m_isPickActive = false;
				}
			}
			else //check collision with ball
			{
				if (m_pickUp.CheckCollision(m_ball))
				{
					m_pickUp.InvokeAction();
					m_isPickActive = false;
				}
			}
		}
	}

	void BrickBreaker::CheckPaddleWallCollision()
	{
		if (m_paddle.GetPosition().GetX() < LEFTLIMIT + m_paddle.GetWidth() / 2)
		{
			m_paddle.SetPosition(LEFTLIMIT + m_paddle.GetWidth() / 2, m_paddle.GetPosition().GetY());
		}
		else if (m_paddle.GetPosition().GetX() > RIGHTLIMIT - m_paddle.GetWidth() / 2)
		{
			m_paddle.SetPosition(RIGHTLIMIT - m_paddle.GetWidth() / 2, m_paddle.GetPosition().GetY());
		}
	}

	void BrickBreaker::CheckBallWallCollision()
	{
		const Vector2& ballPosition = m_ball.GetPosition();

		if (ballPosition.GetX() + m_ball.GetSize() / 2 > RIGHTLIMIT)
		{
			m_ball.GetPosition().SetX(RIGHTLIMIT - m_ball.GetSize() / 2);
			m_ball.SetDirection(-m_ball.GetDirection().GetX(), m_ball.GetDirection().GetY());
			return;
		}
		else if (ballPosition.GetX() - m_ball.GetSize() / 2 < LEFTLIMIT)
		{
			m_ball.SetPosition(LEFTLIMIT + m_ball.GetSize() / 2, m_ball.GetPosition().GetY());
			m_ball.SetDirection(-m_ball.GetDirection().GetX(), m_ball.GetDirection().GetY());
		}

		if (ballPosition.GetY() > BRICKLIMIT_Y)
		{
			m_ball.GetPosition().SetY(BRICKLIMIT_Y);
			m_ball.SetDirection(m_ball.GetDirection().GetX(), -m_ball.GetDirection().GetY());
			return;
		}

		if (ballPosition.GetY() < LOWERLIMIT)
		{
			m_hearts.pop_back();
			--m_heartCounter;
			if (m_heartCounter == 0)
			{
				//playersStatistics.ReadStatistics("..\\Assets\\statisticsBB.txt");
				m_playersStatistics.UpdateStatistics("Player4", true);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "Better luck next time!", nullptr);
				Stop();
			}
			ResetBall();
		}
	}

	void BrickBreaker::CheckBallPaddleCollision()
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
				{
					m_ball.GetDirection().SetX(-difference);
				}

				m_ball.GetDirection().Normalize();
			}
			else
			{
				m_ball.SetDirection(Vector2::down);
			}
		}
	}

	void BrickBreaker::CheckBallBrickCollision()
	{
		for (auto& row : m_bricks)
		{
			for (auto element = row.begin(); element < row.end(); ++element)
			{
				if (m_ball.CheckCollision(*element))
				{
					if (m_isPickCreated == false)
					{
						CreatePickUp(element->GetPosition());
					}

					m_ball.ChangeDirection(*element);
					row.erase(element);
					m_score.AddPoints(1);
					return;
				}
			}
		}
	}

#pragma endregion

#pragma region Input Events

	void BrickBreaker::KeyPressed(const SDL_Keycode& key)
	{
		if (!m_isPaused)
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
		else if (!m_isPaused)
		{
			m_paddle.KeyReleased(key);
		}
	}

	void BrickBreaker::MousePressed(const SDL_MouseButtonEvent& mouse)
	{
		IsInBounds(mouse.x, mouse.y);
	}

	void BrickBreaker::MouseReleased(const SDL_MouseButtonEvent& mouse)
	{
		if (IsInBounds(mouse.x, mouse.y))
		{
			Pause();
		}
	}

#pragma endregion

#pragma region Render Methods

	void BrickBreaker::Render(SDL_Renderer* renderer)
	{
		m_renderer = renderer;
		SDL_Rect rect;
		decltype(auto) scale = GetScale();

		scale.PointToPixel(rect, m_paddle.GetPosition(), m_paddle.GetWidth(), m_paddle.GetHeight());
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(m_renderer, &rect);

		RenderBricks(m_renderer);
		RenderScore(m_renderer);
		RenderHearts(m_renderer);
		RenderButton(m_renderer);

		scale.PointToPixel(rect, m_ball.GetPosition(), m_ball.GetSize(), m_ball.GetSize());
		SDL_RenderCopy(m_renderer, m_ballImage, nullptr, &rect);

		if (m_isPickActive)
		{
			scale.PointToPixel(rect, m_pickUp.GetPosition(), m_pickUp.GetSize(), m_pickUp.GetSize());
			SDL_RenderCopy(renderer, m_pickUpImage, nullptr, &rect);
		}
	}

	void BrickBreaker::RenderBricks(SDL_Renderer* renderer)
	{
		SDL_Rect rect;
		decltype(auto) scale = GetScale();

		for (const auto& row : m_bricks)
		{
			for (const auto& item : row)
			{
				scale.PointToPixel(rect, item.GetPosition(), item.GetWidth(), item.GetHeight());
				SDL_RenderFillRect(renderer, &rect);
			}
		}
	}

	void BrickBreaker::RenderScore(SDL_Renderer* renderer)
	{
		SDL_Rect rect;
		SDL_Texture* fontTexture = m_score.GetText(renderer);

		if (m_score.GetScore() < 10)
		{
			GetScale().PointToPixel(rect, 0.0f, 6.1f, 0.5f, 0.9f);
		}
		else
		{
			GetScale().PointToPixel(rect, 0.0f, 6.1f, 1.0f, 0.9f);
		}

		if (m_buttonFont != nullptr)
		{
			SDL_RenderCopy(renderer, fontTexture, nullptr, &rect);
			SDL_DestroyTexture(fontTexture);
		}
		else
		{
			LOGGING_ERROR("BrickBreaker font not found!");
		}
	}

	void BrickBreaker::RenderHearts(SDL_Renderer* renderer)
	{
		SDL_Rect rect;
		decltype(auto) scale = GetScale();

		for (const auto& iter : m_hearts)
		{
			scale.PointToPixel(rect, iter.GetPosition(), iter.GetWidth(), iter.GetHeight());
			SDL_RenderCopy(renderer, m_heartImage, nullptr, &rect);
		}
	}

	void BrickBreaker::RenderButton(SDL_Renderer* renderer)
	{
		SDL_Rect rect;
		decltype(auto) scale = GetScale();

		scale.PointToPixel(rect, m_pauseButton.GetPosition(), m_pauseButton.GetWidth(), m_pauseButton.GetHeight());
		m_pauseButton.SetRect(rect);
		scale.PointToPixel(rect, m_pauseButton.GetPosition(), m_pauseButton.GetWidth() - 0.2f, m_pauseButton.GetHeight());
		SDL_RenderCopy(renderer, m_pauseButton.GetText(), nullptr, &rect);
	}

#pragma endregion

#pragma region Initialize Methods

	void BrickBreaker::InitializeBricks()
	{
		float offset = 0.5f;
		float x = BRICKLIMIT_X, y = BRICKLIMIT_Y;

		for (auto&& row : m_bricks)
		{
			row.resize(BRICKPERROW);

			for (auto&& brick : row)
			{
				brick.Set(Vector2(x, y), BRICKW, BRICKH);
				x = x + SPACING + BRICKW;
			}

			x = BRICKLIMIT_X;
			y -= offset;
		}
	}

	void BrickBreaker::InitializeHearts()
	{
		float offset = 0.25f;
		float x = LEFTLIMIT + 0.5f;
		float y = LOWERLIMIT + 0.1f;

		m_hearts.resize(m_heartCounter);

		for (auto&& heart : m_hearts)
		{
			heart.Set(Vector2(x, y), HEARTSIZE, HEARTSIZE);
			x += offset + HEARTSIZE;
		}
	}

#pragma endregion

	void BrickBreaker::CreatePickUp(const Vector2& position)
	{
		using Generator = PickUpGenerator::Actions;

		if ((rand() % 100) > PICKUPSPAWNCHANCE)
		{
			m_isPickCreated = true;

			auto type = m_pickUpGenerator.GetPickUpType();
			LOGGING_INFO("BrickBreaker pick-up type is: {0}", static_cast<int>(type));

			switch (m_pickUpGenerator.GetPickUpType())
			{
			case Generator::SPEEDCHANGE:
				m_pickUp = m_pickUpGenerator.CreateSpeedPickUp();
				break;
			case Generator::PADDLESIZECHANGE:
				m_pickUp = m_pickUpGenerator.CreatePaddleSizeChangePickUp(m_paddle, PADDLESIZEDIFFERENCE);
				m_pickUp.SetDirection(Vector2::down);
				m_pickUp.StartMoving();
				break;
			case Generator::PADDLESPEEDCHANGE:
				m_pickUp = m_pickUpGenerator.CreatePaddleSpeedChangePickUp(m_paddle, PADDLESPEEDDIFFERENCE);
				m_pickUp.SetDirection(Vector2::down);
				m_pickUp.StartMoving();
				break;
			case Generator::BALLSIZECHANGE:
				m_pickUp = m_pickUpGenerator.CreateBallSizeChangePickUp(m_ball, BALLSIZEDIFFERENCE);
				break;
			case Generator::BALLSPEEDCHANGE:
				m_pickUp = m_pickUpGenerator.CreateBallSpeedChangePickUp(m_ball, BALLSPEEDDIFFERENCE);
				break;
			case Generator::BONUSPOINTS:
				m_pickUp = m_pickUpGenerator.CreateBonusPointsPickUp(m_score, rand() % MAXSCOREDIFFERENCE + 1);
				break;
			case Generator::REMOVEPOINTS:
				m_pickUp = m_pickUpGenerator.CreateRemovePointsPickUp(m_score, rand() % MAXSCOREDIFFERENCE + 1);
				break;
			default:
				m_isPickCreated = false;
				return;
			}

			m_pickUp.SetPosition(position);
			m_isPickActive = true;
		}
		else
		{
			m_isPickCreated = false;
		}
	}

	bool BrickBreaker::IsInBounds(Sint32 x, Sint32 y)
	{
		return (x > m_pauseButton.GetRect().x && x < m_pauseButton.GetRect().x + m_pauseButton.GetRect().w
			&& y > m_pauseButton.GetRect().y && y < m_pauseButton.GetRect().y + m_pauseButton.GetRect().h);
	}

	void BrickBreaker::Pause()
	{
		m_pauseButton.ChangeFontColor();
		m_pauseButton.SetText(MakeText(m_pauseButton.GetButtonText(), m_pauseButton.GetFontColor(), m_buttonFont));
		Repaint();

		if (!m_isPaused)
		{
			m_lastTimeScale = Time::GetTimeScale();
			Time::SetTimeScale(0);
			m_isPaused = true;
		}
		else
		{
			Time::SetTimeScale(m_lastTimeScale);
			m_isPaused = false;
		}
	}

}