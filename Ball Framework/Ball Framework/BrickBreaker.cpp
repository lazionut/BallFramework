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
#pragma region OUR_IMAGES

#define BALLIMAGE	 m_balls[0].GetImage() 
#define HEARTIMAGE   m_ballImages[0] 
#pragma endregion

	BrickBreaker::BrickBreaker(uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
		: BallGame("BrickBreaker", width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),
		m_heartCounter{ 3 }, m_brickCounter{ BRICKCOUNTER }
	{
		m_bricks = std::vector<std::vector<Brick>>{ BRICKROWS };
		m_playersStatistics = PlayersStatistics{ "..\\Assets\\statisticsBB.txt" };
		m_pauseButton = Button{ Vector2(LEFTLIMIT + 0.5f, UPPERLIMIT + 0.1f), 0.7f, 0.7f, Colors::black, Colors::white, "||" };
	}

	void BrickBreaker::Start()
	{
		m_renderer.SetBackgroundColor(Colors::orange);
		InitializeBricks();
		InitializeHearts();
		InitializeBrickBreakerObjects();
		LoadBrickBreakerImages();
		ResetBall();
		m_pickUpGenerator.SetPickUpDefaultProperties(Vector2::right, PICKUPSIZE, PICKUPSPEEDCHANGE, ACTIONTIME);
		m_pickUpGenerator.SetGeneratorData(BallGame::defaultGeneratorData);
	}

	void BrickBreaker::ResetBall()
	{
		OURBALL.SetDirection(0, 1);
		OURBALL.SetPosition(0, 0);
	}

	void BrickBreaker::OnClose()
	{
		DestroyGameImages();
		SDL_DestroyTexture(m_pickUpImage);
		m_bricks.clear();
		m_outlineSizes.clear();
		m_paddleColors.clear();
		m_paddleOutlines.clear();
		m_players.clear();
		m_balls.clear();
		m_scores.clear();
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
			if (OURBALL.GetPosition().GetY() >= OURPLAYER.GetPosition().GetY() + OURPLAYER.GetHeight() / 2) 
			{
				float difference = abs(OURBALL.GetPosition().GetX() - OURPLAYER.GetPosition().GetX());
				OURBALL.GetDirection().GetY() *= -1;
				if (OURBALL.GetPosition().GetX() >= OURPLAYER.GetPosition().GetX())
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
					if (!m_pickUp.IsActive())
					{
						CreatePickUp(element->GetPosition());
					}

					OURBALL.ChangeDirection(*element);
					row.erase(element);
					--m_brickCounter;

					LOGGING_INFO("BrickBreaker -> ball-brick collision");

					OURSCORE.AddPoints(1);
					OURSCORE.SetText(MakeText(OURSCORE.ConvertToString(), OURSCORE.GetScoreColor()));
					return;
				}
			}

		}
		if (m_brickCounter == 0)
		{
			m_playersStatistics.UpdateStatistics(m_playerName, true);
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "You won! Congratulations!", nullptr);
			Stop();
		}
	}

#pragma endregion

#pragma region Render Methods

	void BrickBreaker::Render(SDL_Renderer* renderer)
	{
		RenderPaddles(renderer);
		RenderBricks(renderer);
		RenderScore(renderer);
		RenderHearts(renderer);
		RenderButton(renderer);
		RenderGameObjects(renderer);
	}

	void BrickBreaker::LoadBrickBreakerImages()
	{
		OURBALL.SetImage(LoadGameImage(Paths::ReturnObjectPath("redBall")));
		m_ballImages.push_back(LoadGameImage(Paths::ReturnObjectPath("redHeart")));
		m_pickUpImage = LoadGameImage(Paths::ReturnObjectPath("star"));

		if (BALLIMAGE == nullptr)
		{
			LOGGING_ERROR("BrickBreaker -> ball image not found!");
			Stop();
			return;
		}

		if (HEARTIMAGE == nullptr)
		{
			LOGGING_ERROR("BrickBreaker -> heart image not found!");
			Stop();
			return;
		}

		if (m_pickUpImage == nullptr)
		{
			LOGGING_ERROR("BrickBreaker -> pick-up image not found!");
			Stop();
			return;
		}
	}

	void BrickBreaker::RenderHearts(SDL_Renderer* renderer)
	{
		SDL_Rect rect;
		decltype(auto) scale = GetScale();

		for (const auto& iter : m_hearts)
		{
			scale.PointToPixel(rect, iter.GetPosition(), iter.GetWidth(), iter.GetHeight());
			SDL_RenderCopy(renderer, HEARTIMAGE, nullptr, &rect);
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

	void BrickBreaker::InitializeBrickBreakerObjects()
	{
		m_players.emplace_back(Paddle(Vector2(0, LOWERLIMIT + 0.5f), 2.0f, 0.25f, Vector2::left, Vector2::right, SDLK_LEFT, SDLK_RIGHT, 5.0)),
		m_paddleColors.push_back(Colors::purple);
		m_paddleOutlines.push_back(Colors::violet);
		m_outlineSizes.push_back(0.05f);

		m_balls.emplace_back(Ball(Vector2(0, LOWERLIMIT + 1.0f), 0.5f, Vector2(0, 1), 4.5f));
		
		m_playerName = m_playersNames.front();

		m_pauseButton.SetText(MakeText(m_pauseButton.GetButtonText(), m_pauseButton.GetFontColor()));

		Score score{ Colors::white };
		score.SetText(MakeText(score.ConvertToString(), score.GetScoreColor()));
		score.SetPosition(0.0f, 6.0f);
		score.SetSize(0.5f, 1.0f);
		m_scores.push_back(score);
	}

#pragma endregion

	void BrickBreaker::CreatePickUp(const Vector2& position)
	{
		if ((Random::Range(100)) > PICKUPSPAWNCHANCE)
		{
			m_pickUp = m_pickUpGenerator.CreateEmptyPickUp(position);
			LOGGING_INFO("BrickBreaker -> pick-up type is: {0}", static_cast<int>(m_pickUp.GetActionType()));
			m_pickUp.SetActive(true);
			m_pickUp.SetVisible(true);
			switch (m_pickUp.GetActionType())
			{
			case Actions::SPEEDCHANGE:
				break;
			case Actions::PADDLESIZECHANGE:
				m_pickUp.SetDirection(Vector2::down);
				m_pickUp.StartMoving();
				break;
			case Actions::PADDLESPEEDCHANGE:
			case Actions::BALLSIZECHANGE:
			case Actions::BALLSPEEDCHANGE:
			case Actions::BONUSPOINTS:m_pickUp.SetVisible(false);
			case Actions::REMOVEPOINTS:m_pickUp.SetVisible(false);
			default:
				m_pickUp.SetActive(false);
				break;
			}
		}
		else
		{
			m_pickUp.SetActive(false);
		}
	}
}