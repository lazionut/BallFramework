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
constexpr auto BRICKCOUNTER = BRICKPERROW * BRICKROWS;

	//pickUp constants
#define PICKUPSPAWNCHANCE 20
#define ACTIONTIME 5.0f
#define PICKUPSIZE 0.25f
#define PICKUPSPEEDCHANGE 2.0f

#define PADDLESIZEDIFFERENCE 1.0f
#define PADDLESPEEDDIFFERENCE 3.0f

#define BALLSIZEDIFFERENCE 1.25f
#define BALLSPEEDDIFFERENCE 4.0f

#define MAXSCOREDIFFERENCE 5

#pragma endregion

#pragma region OUR_OBJECTS

#define OURBALL     m_balls[0] 
#define OURPLAYER   m_players[0] 
#define OURSCORE    m_scores[0] 

#pragma endregion

	BrickBreaker::BrickBreaker(uint16_t width, uint16_t height, TTF_Font* font, const std::vector<std::string>& playersNames, uint32_t flags, uint16_t maxFPS)
		: BallGame("BrickBreaker", width, height, font, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),

		m_renderer{ nullptr }, m_heartImage{ nullptr },
		m_heartCounter{ 3 }, m_brickCounter{ BRICKCOUNTER },
		m_score{ Colors::white },
		m_playerName{ playersNames.front() }
	{
		m_bricks = std::vector<std::vector<Brick>>{ BRICKROWS };
		m_playersStatistics = PlayersStatistics{ "..\\Assets\\statisticsBB.txt" };
		m_pauseButton = Button{ Vector2(LEFTLIMIT + 0.5f, UPPERLIMIT + 0.1f), 0.7f, 0.7f, Colors::black, Colors::white, "||" };
	}

	void BrickBreaker::Start()
	{
		InitializeBricks();
		InitializeHearts();

		m_ballImage = LoadGameImage(Paths::ReturnObjectPath("redBall"));
		m_ballImages.push_back(m_ballImage);
		m_heartImage = LoadGameImage(Paths::ReturnObjectPath("redHeart"));

		m_players.emplace_back(Paddle(Vector2(0, LOWERLIMIT + 0.5f), 2.0f, 0.25f, Vector2::left, Vector2::right, SDLK_LEFT, SDLK_RIGHT, 5.0)),
			m_balls.emplace_back(Ball(Vector2(0, LOWERLIMIT + 1.0f), 0.5f, Vector2(0, 1), 4.5f));
		m_pauseButton.SetText(MakeText(m_pauseButton.GetButtonText(), m_pauseButton.GetFontColor(), m_buttonFont));
		m_score.SetText(MakeText(std::to_string(m_score.GetScore()), Colors::white, m_buttonFont));
		m_scores.push_back(m_score);

		if (m_ballImage == nullptr)
		{
			LOGGING_ERROR("BrickBreaker -> ball image not found!");
			Stop();
			return;
		}

		if (m_heartImage == nullptr)
		{
			LOGGING_ERROR("BrickBreaker -> heart image not found!");
			Stop();
			return;
		}

		ResetBall();

		m_pickUpImage = LoadGameImage(Paths::ReturnObjectPath("star"));
		if (m_pickUpImage == nullptr)
		{
			LOGGING_ERROR("BrickBreaker -> pick-up image not found!");
			Stop();
			return;
		}

		m_pickUpGenerator.SetDefaultProperties(Vector2::right, PICKUPSIZE, PICKUPSPEEDCHANGE, ACTIONTIME);
	}

	void BrickBreaker::ResetBall()
	{
		OURBALL.SetDirection(0, 1);
		OURBALL.SetPosition(0, 0);
	}

	void BrickBreaker::OnClose()
	{
		SDL_DestroyTexture(m_ballImage);
		SDL_DestroyTexture(m_heartImage);
		SDL_DestroyTexture(m_pickUpImage);
		m_bricks.erase(m_bricks.begin(), m_bricks.end());
		Time::SetTimeScale(1.0f);
	}

#pragma region Collision Methods

	void BrickBreaker::CheckCollision()
	{
		CheckPaddleWallCollision();
		CheckBallWallCollision();
		CheckBallPaddleCollision();
		CheckBallBrickCollision();
		CheckPickUpCollision();
	}

	void BrickBreaker::CheckPaddleWallCollision()
	{
		if (OURPLAYER.GetPosition().GetX() < LEFTLIMIT + OURPLAYER.GetWidth() / 2)
		{
			OURPLAYER.SetPosition(LEFTLIMIT + OURPLAYER.GetWidth() / 2, OURPLAYER.GetPosition().GetY());
		}
		else if (OURPLAYER.GetPosition().GetX() > RIGHTLIMIT - OURPLAYER.GetWidth() / 2)
		{
			OURPLAYER.SetPosition(RIGHTLIMIT - OURPLAYER.GetWidth() / 2, OURPLAYER.GetPosition().GetY());
		}
	}

	void BrickBreaker::CheckBallWallCollision()
	{
		const Vector2& ballPosition = OURBALL.GetPosition();

		if (ballPosition.GetX() + OURBALL.GetSize() / 2 > RIGHTLIMIT)
		{
			OURBALL.GetPosition().SetX(RIGHTLIMIT - OURBALL.GetSize() / 2);
			OURBALL.SetDirection(-OURBALL.GetDirection().GetX(), OURBALL.GetDirection().GetY());
			LOGGING_INFO("BrickBreaker -> ball-right wall collision");
		}
		else if (ballPosition.GetX() - OURBALL.GetSize() / 2 < LEFTLIMIT)
		{
			OURBALL.SetPosition(LEFTLIMIT + OURBALL.GetSize() / 2, OURBALL.GetPosition().GetY());
			OURBALL.SetDirection(-OURBALL.GetDirection().GetX(), OURBALL.GetDirection().GetY());
			LOGGING_INFO("BrickBreaker -> ball-left wall collision");
		}

		if (ballPosition.GetY() > BRICKLIMIT_Y)
		{
			OURBALL.GetPosition().SetY(BRICKLIMIT_Y);
			OURBALL.SetDirection(OURBALL.GetDirection().GetX(), -OURBALL.GetDirection().GetY());
			LOGGING_INFO("BrickBreaker -> ball-upper wall collision");
		}

		if (ballPosition.GetY() < LOWERLIMIT)
		{
			m_hearts.pop_back();
			--m_heartCounter;
			LOGGING_INFO("BrickBreaker -> lose one heart");
			if (m_heartCounter == 0)
			{
				//playersStatistics.ReadStatistics("..\\Assets\\statisticsBB.txt");
				m_playersStatistics.UpdateStatistics(m_playerName, false);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "Better luck next time!", nullptr);
				Stop();
			}
			ResetBall();
		}
	}

	void BrickBreaker::CheckBallPaddleCollision()
	{
		if (OURBALL.CheckCollision(OURPLAYER))
		{
			if (OURBALL.GetPosition().GetY() >= OURPLAYER.GetPosition().GetY() + OURPLAYER.GetHeight() / 2) //temporary solution to a bug
			{
				//OURBALL.ChangeDirection(OURPLAYER);
				float difference = abs(OURBALL.GetPosition().GetX() - OURPLAYER.GetPosition().GetX());
				OURBALL.GetDirection().GetY() *= -1;

				//if (OURBALL.GetDirection().GetX() >= 0) //prima versiune

				if (OURBALL.GetPosition().GetX() >= OURPLAYER.GetPosition().GetX())
					//asta e a doua optiune de design in care mingea isi schimba dir 
					//pe axa x in functie de unde pica pe paleta
				{
					OURBALL.GetDirection().SetX(difference);
				}
				else
				{
					OURBALL.GetDirection().SetX(-difference);
				}

				OURBALL.GetDirection().Normalize();
			}
			else
			{
				OURBALL.SetDirection(Vector2::down);
				LOGGING_INFO("BrickBreaker -> ball-paddle lose collision");
			}
		}
	}

	void BrickBreaker::CheckBallBrickCollision()
	{
		for (auto& row : m_bricks)
		{
			for (auto element = row.begin(); element < row.end(); ++element)
			{
				if (OURBALL.CheckCollision(*element))
				{
					if (m_isPickCreated == false)
					{
						CreatePickUp(element->GetPosition());
					}

					OURBALL.ChangeDirection(*element);
					row.erase(element);
					--m_brickCounter;

					LOGGING_INFO("BrickBreaker -> ball-brick collision");

					OURSCORE.AddPoints(1);
					OURSCORE.SetText(MakeText(OURSCORE.ConvertToString(), Colors::white, m_buttonFont));
					return;
				}
			}

		}
		if (m_brickCounter == 0)
		{
			//playersStatistics.ReadStatistics("..\\Assets\\statisticsBB.txt");
			m_playersStatistics.UpdateStatistics(m_playerName, true);
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "You won! Congratulations!", nullptr);
			Stop();
		}
	}

#pragma endregion

#pragma region Render Methods

	void BrickBreaker::Render(SDL_Renderer* renderer)
	{
		m_renderer = renderer;
		SDL_Rect rect;
		decltype(auto) scale = GetScale();

		scale.PointToPixel(rect, OURPLAYER.GetPosition(), OURPLAYER.GetWidth(), OURPLAYER.GetHeight());
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(m_renderer, &rect);

		RenderBricks(m_renderer);
		RenderScore(m_renderer);
		RenderHearts(m_renderer);
		RenderButton(m_renderer);

		scale.PointToPixel(rect, OURBALL.GetPosition(), OURBALL.GetSize(), OURBALL.GetSize());
		SDL_RenderCopy(m_renderer, m_ballImage, nullptr, &rect);

		if (m_isPickActive)
		{
			scale.PointToPixel(rect, m_pickUp.GetPosition(), m_pickUp.GetSize(), m_pickUp.GetSize());
			SDL_RenderCopy(renderer, m_pickUpImage, nullptr, &rect);
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

#pragma endregion

#pragma region Initialize Methods

	void BrickBreaker::InitializeBricks()
	{
		float offset = 0.5f;
		float x = BRICKLIMIT_X, y = BRICKLIMIT_Y;

		for (auto&& row : m_bricks)
		{
			row.resize(BRICKPERROW); //MODIFY

			for (auto&& brick : row)
			{
				brick.Set(Vector2(x, y), BRICKW, BRICKH);
				brick.SetColor(Colors::white);
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
			LOGGING_INFO("BrickBreaker -> pick-up type is: {0}", static_cast<int>(type));

			switch (m_pickUpGenerator.GetPickUpType())
			{
			case Generator::SPEEDCHANGE:
				m_pickUp = m_pickUpGenerator.CreateSpeedPickUp();
				break;
			case Generator::PADDLESIZECHANGE:
				m_pickUp = m_pickUpGenerator.CreatePaddleSizeChangePickUp(OURPLAYER, PADDLESIZEDIFFERENCE);
				m_pickUp.SetDirection(Vector2::down);
				m_pickUp.StartMoving();
				break;
			case Generator::PADDLESPEEDCHANGE:
				m_pickUp = m_pickUpGenerator.CreatePaddleSpeedChangePickUp(OURPLAYER, PADDLESPEEDDIFFERENCE);
				m_pickUp.SetDirection(Vector2::down);
				m_pickUp.StartMoving();
				break;
			case Generator::BALLSIZECHANGE:
				m_pickUp = m_pickUpGenerator.CreateBallSizeChangePickUp(OURBALL, BALLSIZEDIFFERENCE);
				break;
			case Generator::BALLSPEEDCHANGE:
				m_pickUp = m_pickUpGenerator.CreateBallSpeedChangePickUp(OURBALL, BALLSPEEDDIFFERENCE);
				break;
			case Generator::BONUSPOINTS:
				m_pickUp = m_pickUpGenerator.CreateBonusPointsPickUp(OURSCORE, rand() % MAXSCOREDIFFERENCE + 1);
				break;
			case Generator::REMOVEPOINTS:
				m_pickUp = m_pickUpGenerator.CreateRemovePointsPickUp(OURSCORE, rand() % MAXSCOREDIFFERENCE + 1);
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

}