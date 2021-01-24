#include "BrickBreakerCoop.h"

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

#define OURBALL    m_balls[0] 
#define PLAYER1    m_players[0] 
#define PLAYER2    m_players[1] 
#define OURSCORE   m_scores[0] 
#pragma endregion

#pragma region OUR_IMAGES

#define BALLIMG    m_balls[0].GetImage() 
#define HEARTIMG   m_ballImages[0]  
#pragma endregion

	BrickBreakerCoop::BrickBreakerCoop(uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS) :
		BallGame("BrickBreakerCoop", width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),
		m_heartCounter{ 3 }, m_brickCounter{ BRICKCOUNTER }
	{
		m_bricks = std::vector<std::vector<Brick>>{ BRICKROWS };
		m_playersStatistics = PlayersStatistics{ "..\\Assets\\statisticsBBC.txt" };
		m_pauseButton = Button{ Vector2(LEFTLIMIT + 0.5f, UPPERLIMIT + 0.1f), 0.7f, 0.7f, Colors::black, Colors::white, "||" };
	}

#pragma region Initialize Methods
	void BrickBreakerCoop::Start()
	{
		m_renderer.SetBackgroundColor(Colors::yellow);
		InitializeBricks();
		InitializeHearts();
		InitializeBrickBreakerCoopObjects();
		LoadBrickBreakerCoopImages();
		ResetBall();

		m_pickUpGenerator.SetPickUpDefaultProperties(Vector2::right, PICKUPSIZE, PICKUPSPEEDCHANGE, ACTIONTIME);
		m_pickUpGenerator.SetGeneratorData(GeneratorData(2.0f, 5.0f, 1.0f, 5.0f, 2.0f, 5));
	}

	void BrickBreakerCoop::InitializeBricks()
	{
		float offset = 0.5f;
		float x = BRICKLIMIT_X, y = BRICKLIMIT_Y;

		for (auto&& row : m_bricks)
		{
			row.resize(BRICKPERROW); //MODIFY

			for (auto&& brick : row)
			{
				brick.Set(Vector2(x, y), BRICKW, BRICKH);
				brick.SetColor(Colors::orange);
				x = x + SPACING + BRICKW;
			}

			x = BRICKLIMIT_X;
			y -= offset;
		}
	}

	void BrickBreakerCoop::InitializeHearts()
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
	void BrickBreakerCoop::LoadBrickBreakerCoopImages()
	{
		OURBALL.SetImage(LoadGameImage(Paths::ReturnObjectPath("redBall")));
		m_ballImages.push_back(LoadGameImage(Paths::ReturnObjectPath("redHeart")));
		m_pickUpImage = LoadGameImage(Paths::ReturnObjectPath("star"));

		if (BALLIMG == nullptr)
		{
			LOGGING_ERROR("BrickBreaker -> ball image not found!");
			Stop();
			return;
		}

		if (HEARTIMG == nullptr)
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
	void BrickBreakerCoop::InitializeBrickBreakerCoopObjects()
	{
		m_balls.emplace_back(Ball(Vector2(0, LOWERLIMIT + 1.0f), 0.5f, Vector2(0, 1), 4.5f));

		m_players.emplace_back(Paddle(Vector2(LEFTLIMIT + 2.0f, LOWERLIMIT + 0.5f), 2.0f, 0.25f, Vector2::left, Vector2::right, SDLK_a, SDLK_d, 5.0));
		m_players.emplace_back(Paddle(Vector2(RIGHTLIMIT - 2.0f, LOWERLIMIT + 0.5f), 2.0f, 0.25f, Vector2::left, Vector2::right, SDLK_LEFT, SDLK_RIGHT, 5.0));
		m_paddleColors.push_back(Colors::blue);
		m_paddleOutlines.push_back(Colors::orange);
		m_outlineSizes.push_back(0.05f);

		m_paddleColors.push_back(Colors::green);
		m_paddleOutlines.push_back(Colors::violet);
		m_outlineSizes.push_back(0.05f);

		m_pauseButton.SetText(MakeText(m_pauseButton.GetButtonText(), m_pauseButton.GetFontColor()));

		m_player1Name = m_playersNames.front();
		m_player2Name = m_playersNames.back();

		Score score{ Colors::red };
		score.SetText(MakeText(std::to_string(score.GetScore()), Colors::red));
		score.SetSize(0.5f, 1.0f);
		score.SetPosition(Vector2(0, UPPERLIMIT + 0.1f));
		m_scores.push_back(score);

	}
#pragma endregion

#pragma region Redering Methods
	void BrickBreakerCoop::Render(SDL_Renderer* renderer)
	{
		RenderPaddles(renderer);
		RenderBricks(renderer);
		RenderScore(renderer);
		RenderHearts(renderer);
		RenderButton(renderer);
		RenderGameObjects(renderer);
	}

	void BrickBreakerCoop::RenderHearts(SDL_Renderer* renderer)
	{
		SDL_Rect rect;
		decltype(auto) scale = GetScale();

		for (const auto& iter : m_hearts)
		{
			scale.PointToPixel(rect, iter.GetPosition(), iter.GetWidth(), iter.GetHeight());
			SDL_RenderCopy(renderer, HEARTIMG, nullptr, &rect);
		}
	}
#pragma endregion

#pragma region Collision Methods
	void BrickBreakerCoop::CheckCollision()
	{
		CheckPaddleWallCollision();
		CheckBallWallCollision();
		CheckBallPaddleCollision();
		CheckBallBrickCollision();
		CheckPickUpCollision();
	}

	void BrickBreakerCoop::CheckPaddleWallCollision()
	{
		if (PLAYER1.GetPosition().GetX() < LEFTLIMIT + PLAYER1.GetWidth() / 2)
		{
			PLAYER1.SetPosition(LEFTLIMIT + PLAYER1.GetWidth() / 2, PLAYER1.GetPosition().GetY());
		}
		else if (PLAYER1.GetPosition().GetX() > RIGHTLIMIT - PLAYER1.GetWidth() / 2)
		{
			PLAYER1.SetPosition(RIGHTLIMIT - PLAYER1.GetWidth() / 2, PLAYER1.GetPosition().GetY());
		}

		if (PLAYER2.GetPosition().GetX() < LEFTLIMIT + PLAYER2.GetWidth() / 2)
		{
			PLAYER2.SetPosition(LEFTLIMIT + PLAYER2.GetWidth() / 2, PLAYER2.GetPosition().GetY());
		}
		else if (PLAYER2.GetPosition().GetX() > RIGHTLIMIT - PLAYER2.GetWidth() / 2)
		{
			PLAYER2.SetPosition(RIGHTLIMIT - PLAYER2.GetWidth() / 2, PLAYER2.GetPosition().GetY());
		}
	}

	void BrickBreakerCoop::CheckBallPaddleCollision()
	{
		if (OURBALL.CheckCollision(PLAYER1) || OURBALL.CheckCollision(PLAYER2))
		{
			if (OURBALL.GetPosition().GetY() >= PLAYER1.GetPosition().GetY() + PLAYER1.GetHeight() / 2
				|| OURBALL.GetPosition().GetY() >= PLAYER2.GetPosition().GetY() + PLAYER2.GetHeight() / 2)
			{
				float difference;
				if (OURBALL.GetPosition().GetX() > PLAYER1.GetPosition().GetX() - PLAYER1.GetWidth() / 2 && OURBALL.GetPosition().GetX() < PLAYER1.GetPosition().GetX() + PLAYER1.GetWidth())
				{
					difference = abs(OURBALL.GetPosition().GetX() - PLAYER1.GetPosition().GetX());

					if (OURBALL.GetPosition().GetX() >= PLAYER1.GetPosition().GetX())
						//mingea isi schimba dir  axa x in functie de unde pica pe paleta
					{
						OURBALL.GetDirection().SetX(difference);
					}
					else
					{
						OURBALL.GetDirection().SetX(-difference);
					}
					m_lastPaddleHit = true;
				}
				if (OURBALL.GetPosition().GetX() > PLAYER2.GetPosition().GetX() - PLAYER2.GetWidth() / 2 && OURBALL.GetPosition().GetX() < PLAYER2.GetPosition().GetX() + PLAYER2.GetWidth())
				{
					difference = abs(OURBALL.GetPosition().GetX() - PLAYER2.GetPosition().GetX());
					if (OURBALL.GetPosition().GetX() >= PLAYER2.GetPosition().GetX())
						//mingea isi schimba dir  axa x in functie de unde pica pe paleta
					{
						OURBALL.GetDirection().SetX(difference);
					}
					else
					{
						OURBALL.GetDirection().SetX(-difference);
					}
					m_lastPaddleHit = false;
				}
				OURBALL.GetDirection().GetY() *= -1;


				OURBALL.GetDirection().Normalize();
			}
			else
			{
				OURBALL.SetDirection(Vector2::down);
				LOGGING_INFO("BrickBreaker -> ball-paddle lose collision");
			}
		}
	}

	void BrickBreakerCoop::CheckBallWallCollision()
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

				m_playersStatistics.UpdateStatistics(m_player1Name, false);
				m_playersStatistics.UpdateStatistics(m_player2Name, false);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "Better luck next time!", nullptr);
				Stop();
			}
			ResetBall();
		}
	}

	void BrickBreakerCoop::CheckBallBrickCollision()
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
			//playersStatistics.ReadStatistics("..\\Assets\\statisticsBB.txt");
			m_playersStatistics.UpdateStatistics(m_player1Name, true);
			m_playersStatistics.UpdateStatistics(m_player2Name, true);
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "You won! Congratulations!", nullptr);
			Stop();
		}
	}
#pragma endregion

	void BrickBreakerCoop::OnClose()
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
		m_bricks.erase(m_bricks.begin(), m_bricks.end());
		Time::SetTimeScale(1.0f);
	}

	void BrickBreakerCoop::ResetBall()
	{
		OURBALL.SetDirection(pow(-1, Random::Range(2)), 1);
		OURBALL.SetPosition(0, 0);
	}

	void BrickBreakerCoop::CreatePickUp(const Vector2& position)
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