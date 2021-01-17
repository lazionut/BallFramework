#include "BrickBreakerVS.h"
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
#define PICKUPSIZECHANGE 0.25f
#define PICKUPSPEEDCHANGE 2.0f

#define PADDLESIZEDIFFERENCE 1.0f
#define PADDLESPEEDDIFFERENCE 3.0f

#define BALLSIZEDIFFERENCE 1.25f
#define BALLSPEEDDIFFERENCE 4.0f

#define MAXSCOREDIFFERENCE 5

#pragma endregion

#pragma region OUR_OBJECTS

#define BALL1      m_balls[0] 
#define BALL2      m_balls[1] 
#define PLAYER1    m_players[0] 
#define PLAYER2    m_players[1] 
#define SCORE1     m_scores[0] 
#define SCORE2     m_scores[1] 

#pragma endregion

	BallFramework::BrickBreakerVS::BrickBreakerVS(uint16_t width, uint16_t height, TTF_Font* font, const std::vector<std::string>& playersNames, uint32_t flags, uint16_t maxFPS) :
		BallGame("BrickBreakerVS", width, height, font, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),
		m_renderer{ nullptr }, m_heartImage{ nullptr },
		m_heartCounter1{ 3 }, m_brickCounter1{ BRICKCOUNTER },
		m_heartCounter2{ 3 }, m_brickCounter2{ BRICKCOUNTER },
		m_score1{ Colors::red },
		m_score2{ Colors::white },
		m_player1Name{ playersNames.front() }
	{
		m_bricks = std::vector<std::vector<Brick>>{ BRICKROWS };
		m_playersStatistics = PlayersStatistics{ "..\\Assets\\statisticsBBVS.txt" };
		m_pauseButton = Button{ Vector2(LEFTLIMIT + 0.5f, UPPERLIMIT + 0.1f), 0.7f, 0.7f, Colors::black, Colors::white, "||" };
	}

	void BrickBreakerVS::Start()
	{
		m_ballImage = LoadGameImage(Paths::ReturnObjectPath("redBall")); //first red
		m_heartImage = LoadGameImage(Paths::ReturnObjectPath("redHeart"));
		m_ballImages.push_back(m_ballImage);
		m_ballImage = LoadGameImage(Paths::ReturnObjectPath("ball")); // second white
		m_ballImages.push_back(m_ballImage);
		m_balls.emplace_back(Ball(Vector2(LEFTLIMIT + 2.0f, LOWERLIMIT + 1.0f), 0.5f, Vector2(0, 1), 4.5f));
		m_balls.emplace_back(Ball(Vector2(RIGHTLIMIT - 2.0f, LOWERLIMIT + 1.0f), 0.5f, Vector2(0, 1), 4.5f));
		BALL1.SetId(1);
		BALL2.SetId(2);
		InitializeBricks();
		InitializeHearts();

		m_players.emplace_back(Paddle(Vector2(LEFTLIMIT + 2.0f, LOWERLIMIT + 0.5f), 2.0f, 0.25f, Vector2::left, Vector2::right, SDLK_a, SDLK_d, 5.0));
		m_players.emplace_back(Paddle(Vector2(RIGHTLIMIT - 2.0f, LOWERLIMIT + 0.5f), 2.0f, 0.25f, Vector2::left, Vector2::right, SDLK_LEFT, SDLK_RIGHT, 5.0));

		m_pauseButton.SetText(MakeText(m_pauseButton.GetButtonText(), m_pauseButton.GetFontColor(), m_buttonFont));

		m_score1.SetText(MakeText(std::to_string(m_score1.GetScore()), Colors::red, m_buttonFont));
		m_score1.SetHeight(1.0f);
		m_score1.SetWidth(0.5f);
		m_score1.SetPosition(Vector2(LEFTLIMIT + 2.0f, UPPERLIMIT + 0.1f));
		m_scores.push_back(m_score1);

		m_score2.SetText(MakeText(std::to_string(m_score2.GetScore()), Colors::white, m_buttonFont));
		m_score2.SetHeight(1.0f);
		m_score2.SetWidth(0.5f);
		m_score2.SetPosition(Vector2(RIGHTLIMIT - 2.0f, UPPERLIMIT + 0.1f));
		m_scores.push_back(m_score2);

		if (m_ballImage == nullptr)
		{
			LOGGING_ERROR("BrickBreaker -> ball image not found!");
			Stop();
			return;
		}

		if (m_ballImage == nullptr)
		{
			LOGGING_ERROR("BrickBreaker -> ball image 2 not found!");
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
		ResetBall2();

		m_pickUpImage = LoadGameImage(Paths::ReturnObjectPath("star"));
		if (m_pickUpImage == nullptr)
		{
			LOGGING_ERROR("BrickBreaker -> pick-up image not found!");
			Stop();
			return;
		}

		m_pickUpGenerator.SetDefaultProperties(Vector2::right, PICKUPSIZECHANGE, PICKUPSPEEDCHANGE, ACTIONTIME);

		m_paddleColors.push_back(Colors::red);
		m_paddleOutlines.push_back(Colors::yellow);
		m_outlineSizes.push_back(0.05f);

		m_paddleColors.push_back(Colors::white);
		m_paddleOutlines.push_back(Colors::blue);
		m_outlineSizes.push_back(0.05f);
	}

	void BrickBreakerVS::OnClose()
	{
		SDL_DestroyTexture(m_ballImage);
		SDL_DestroyTexture(m_heartImage);
		SDL_DestroyTexture(m_pickUpImage);
		m_bricks.erase(m_bricks.begin(), m_bricks.end());
		Time::SetTimeScale(1.0f);
	}

	void BrickBreakerVS::CheckCollision()
	{
		CheckPaddleWallCollision();
		CheckBallWallCollision();
		CheckBallPaddleCollision();
		CheckBallBrickCollision();
		CheckPickUpCollision();
	}

	void BrickBreakerVS::Render(SDL_Renderer* renderer)
	{
		m_renderer = renderer;
		SDL_Rect rect;
		decltype(auto) scale = GetScale();

		RenderPaddles(m_renderer);
		RenderBricks(m_renderer);
		RenderScore(m_renderer);
		RenderHearts(m_renderer);
		RenderButton(m_renderer);
		RenderGameObjects(m_renderer);
	}

	void BrickBreakerVS::ResetBall()
	{
		BALL1.SetDirection(Vector2::up);
		BALL1.SetPosition(LEFTLIMIT + 2.0f, LOWERLIMIT + 5.0f);
	}

	void BrickBreakerVS::ResetBall2()
	{
		BALL2.SetDirection(Vector2::up);
		BALL2.SetPosition(RIGHTLIMIT - 2.0f, LOWERLIMIT + 5.0f);
	}

	void BrickBreakerVS::CheckPaddleWallCollision()
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

	void BrickBreakerVS::CheckBallPaddleCollision()
	{
		if (BALL1.CheckCollision(PLAYER1))
		{
			if (BALL1.GetPosition().GetY() >= PLAYER1.GetPosition().GetY() + PLAYER1.GetHeight() / 2) //temporary solution to a bug
			{
				float difference = abs(BALL1.GetPosition().GetX() - PLAYER1.GetPosition().GetX());
				BALL1.GetDirection().GetY() *= -1;

				if (BALL1.GetPosition().GetX() >= PLAYER1.GetPosition().GetX())
					// mingea isi schimba dir pe axa x in functie de unde pica pe paleta
				{
					BALL1.GetDirection().SetX(difference);
				}
				else
				{
					BALL1.GetDirection().SetX(-difference);
				}

				BALL1.GetDirection().Normalize();
			}
			else
			{
				BALL1.SetDirection(Vector2::down);
				LOGGING_INFO("BrickBreaker -> ball1-paddle lose collision");
			}
		}

		if (BALL2.CheckCollision(PLAYER2))
		{
			if (BALL2.GetPosition().GetY() >= PLAYER2.GetPosition().GetY() + PLAYER2.GetHeight() / 2) //temporary solution to a bug
			{
				float difference = abs(BALL2.GetPosition().GetX() - PLAYER2.GetPosition().GetX());
				BALL2.GetDirection().GetY() *= -1;

				if (BALL2.GetPosition().GetX() >= PLAYER2.GetPosition().GetX())
					//mingea isi schimba dir pe axa x in functie de unde pica pe paleta
				{
					BALL2.GetDirection().SetX(difference);
				}
				else
				{
					BALL2.GetDirection().SetX(-difference);
				}

				BALL2.GetDirection().Normalize();
			}
			else
			{
				BALL2.SetDirection(Vector2::down);
				LOGGING_INFO("BrickBreaker -> ball2-paddle lose collision");
			}
		}
	}

	void BrickBreakerVS::CheckBallWallCollision()
	{
		const Vector2& ballPosition = BALL1.GetPosition();
		const Vector2& ballPosition2 = BALL2.GetPosition();

		if (ballPosition.GetX() + BALL1.GetSize() / 2 > RIGHTLIMIT)
		{
			BALL1.GetPosition().SetX(RIGHTLIMIT - BALL1.GetSize() / 2);
			BALL1.SetDirection(-BALL1.GetDirection().GetX(), BALL1.GetDirection().GetY());
			LOGGING_INFO("BrickBreaker -> ball1-right wall collision");
		}
		else if (ballPosition.GetX() - BALL1.GetSize() / 2 < LEFTLIMIT)
		{
			BALL1.SetPosition(LEFTLIMIT + BALL1.GetSize() / 2, BALL1.GetPosition().GetY());
			BALL1.SetDirection(-BALL1.GetDirection().GetX(), BALL1.GetDirection().GetY());
			LOGGING_INFO("BrickBreaker -> ball1-left wall collision");
		}

		if (ballPosition2.GetX() + BALL2.GetSize() / 2 > RIGHTLIMIT)
		{
			BALL2.GetPosition().SetX(RIGHTLIMIT - BALL2.GetSize() / 2);
			BALL2.SetDirection(-BALL2.GetDirection().GetX(), BALL2.GetDirection().GetY());
			LOGGING_INFO("BrickBreaker -> ball2-right wall collision");
		}
		else if (ballPosition2.GetX() - BALL2.GetSize() / 2 < LEFTLIMIT)
		{
			BALL2.SetPosition(LEFTLIMIT + BALL2.GetSize() / 2, BALL2.GetPosition().GetY());
			BALL2.SetDirection(-BALL2.GetDirection().GetX(), BALL2.GetDirection().GetY());
			LOGGING_INFO("BrickBreaker -> ball2-left wall collision");
		}


		if (ballPosition.GetY() > BRICKLIMIT_Y)
		{
			BALL1.GetPosition().SetY(BRICKLIMIT_Y);
			BALL1.SetDirection(BALL1.GetDirection().GetX(), -BALL1.GetDirection().GetY());
			LOGGING_INFO("BrickBreaker -> ball-upper wall collision");
		}

		if (ballPosition2.GetY() > BRICKLIMIT_Y)
		{
			BALL2.GetPosition().SetY(BRICKLIMIT_Y);
			BALL2.SetDirection(BALL2.GetDirection().GetX(), -BALL2.GetDirection().GetY());
			LOGGING_INFO("BrickBreaker -> ball2-upper wall collision");
		}

		if (ballPosition.GetY() < LOWERLIMIT)
		{
			m_hearts1.pop_back();
			--m_heartCounter1;
			LOGGING_INFO("BrickBreaker -> player1 lose one heart");
			if (m_heartCounter1 == 0)
			{

				m_playersStatistics.UpdateStatistics(m_player1Name, false);
				m_playersStatistics.UpdateStatistics(m_player2Name, true);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", m_player2Name.append(" wins!").c_str(), nullptr);
				Stop();
			}
			ResetBall();
		}

		if (ballPosition2.GetY() < LOWERLIMIT)
		{
			m_hearts2.pop_back();
			--m_heartCounter2;
			LOGGING_INFO("BrickBreaker -> player2 lose one heart");
			if (m_heartCounter2 == 0)
			{

				m_playersStatistics.UpdateStatistics(m_player1Name, true);
				m_playersStatistics.UpdateStatistics(m_player2Name, false);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", m_player1Name.append(" wins!").c_str(), nullptr);
				Stop();
			}
			ResetBall2();
		}
	}

	void BrickBreakerVS::CheckBallBrickCollision()
	{
		for (auto& row : m_bricks)
		{
			for (auto element = row.begin(); element < row.end(); ++element)
			{
				if (BALL1.CheckCollision(*element))
				{
					BALL1.ChangeDirection(*element);

					if (element->GetId() == BALL1.GetId())
					{
						if (m_isPickCreated == false)
						{
							CreatePickUp(element->GetPosition());

						}
						row.erase(element);
						--m_brickCounter1;
						SCORE1.AddPoints(1);
						SCORE1.SetText(MakeText(SCORE1.ConvertToString(), Colors::red, m_buttonFont));
					}
					LOGGING_INFO("BrickBreaker -> ball1-brick collision");

					return;
				}

				if (BALL2.CheckCollision(*element))
				{
					BALL2.ChangeDirection(*element);
					if (element->GetId() == BALL2.GetId())
					{
						if (m_isPickCreated == false)
						{
							CreatePickUp(element->GetPosition());
						}

						row.erase(element);
						--m_brickCounter2;
						SCORE2.AddPoints(1);
						SCORE2.SetText(MakeText(SCORE2.ConvertToString(), Colors::white, m_buttonFont));
					}
					LOGGING_INFO("BrickBreaker -> ball2-brick collision");

					return;
				}
			}

		}
		if (m_brickCounter1 == 0)
		{
			//playersStatistics.ReadStatistics("..\\Assets\\statisticsBB.txt");
			m_playersStatistics.UpdateStatistics(m_player1Name, true);
			m_playersStatistics.UpdateStatistics(m_player2Name, false);
			//m_playersStatistics.UpdateStatistics(m_player2Name, true);
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "Player1 won! Congratulations!", nullptr);
			Stop();
		}
		if (m_brickCounter2 == 0)
		{
			//playersStatistics.ReadStatistics("..\\Assets\\statisticsBB.txt");
			m_playersStatistics.UpdateStatistics(m_player1Name, false);
			m_playersStatistics.UpdateStatistics(m_player1Name, true);
			//m_playersStatistics.UpdateStatistics(m_player2Name, true);
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "Player2 won! Congratulations!", nullptr);
			Stop();
		}
	}

	void BrickBreakerVS::CheckPickUpCollision()
	{
		if (m_isPickActive)
		{
			if (m_pickUp.IsMoving())
			{
				if (m_pickUp.CheckCollision(PLAYER1))
				{
					m_pickUp.InvokeAction();
					m_isPickActive = false;
					LOGGING_INFO("BrickBreaker -> player paddle-pick-up collision");
					m_lastPaddleHit = true;
				}
				if (m_pickUp.CheckCollision(PLAYER2))
				{
					m_pickUp.InvokeAction();
					m_isPickActive = false;
					LOGGING_INFO("BrickBreaker -> player paddle-pick-up collision");
					m_lastPaddleHit = false;
				}
			}
			else
			{
				if (m_pickUp.CheckCollision(BALL1)) // TO DO 
				{
					m_pickUp.InvokeAction();
					m_isPickActive = false;
					LOGGING_INFO("BrickBreaker -> ball-pick-up collision");
					m_switchBall = true;
				}
				if (m_pickUp.CheckCollision(BALL2)) // TO DO 
				{
					m_pickUp.InvokeAction();
					m_isPickActive = false;
					LOGGING_INFO("BrickBreaker -> ball-pick-up collision");
					m_switchBall = false;
				}
			}
		}
	}

	void BrickBreakerVS::InitializeBricks()
	{
		float offset = 0.5f;
		float x = BRICKLIMIT_X, y = BRICKLIMIT_Y;
		int8_t switchColor = 1;
		for (auto&& row : m_bricks)
		{
			row.resize(BRICKPERROW); //MODIFY

			for (auto&& brick : row)
			{
				brick.Set(Vector2(x, y), BRICKW, BRICKH);
				if (switchColor > 0)
				{
					brick.SetColor(Colors::red);
					brick.SetId(BALL1.GetId());
				}
				else
				{
					brick.SetColor(Colors::white);
					brick.SetId(BALL2.GetId());
				}
				x = x + SPACING + BRICKW;
				switchColor *= -1;
			}

			x = BRICKLIMIT_X;
			y -= offset;
		}
	}

	void BrickBreakerVS::InitializeHearts()
	{
		float offset = 0.25f;
		float x = LEFTLIMIT + 0.5f;
		float y = LOWERLIMIT + 0.1f;

		m_hearts1.resize(m_heartCounter1);

		for (auto&& heart : m_hearts1)
		{
			heart.Set(Vector2(x, y), HEARTSIZE, HEARTSIZE);
			x += offset + HEARTSIZE;
		}
		m_hearts2.resize(m_heartCounter2);

		x = RIGHTLIMIT - 0.5f;

		for (auto&& heart : m_hearts2)
		{
			heart.Set(Vector2(x, y), HEARTSIZE, HEARTSIZE);
			x -= offset + HEARTSIZE;
		}
	}

	void BrickBreakerVS::RenderHearts(SDL_Renderer* renderer)
	{
		SDL_Rect rect;
		decltype(auto) scale = GetScale();

		for (const auto& iter : m_hearts1)
		{
			scale.PointToPixel(rect, iter.GetPosition(), iter.GetWidth(), iter.GetHeight());
			SDL_RenderCopy(renderer, m_heartImage, nullptr, &rect);
		}
		for (const auto& iter : m_hearts2)
		{
			scale.PointToPixel(rect, iter.GetPosition(), iter.GetWidth(), iter.GetHeight());
			SDL_RenderCopy(renderer, m_heartImage, nullptr, &rect);
		}
	}

	void BrickBreakerVS::CreatePickUp(const Vector2& position)
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
				if (m_lastPaddleHit)
					m_pickUp = m_pickUpGenerator.CreatePaddleSizeChangePickUp(PLAYER1, PADDLESIZEDIFFERENCE);
				else
					m_pickUp = m_pickUpGenerator.CreatePaddleSizeChangePickUp(PLAYER2, PADDLESIZEDIFFERENCE);
				m_pickUp.SetDirection(Vector2::down);
				m_pickUp.StartMoving();
				break;
			case Generator::PADDLESPEEDCHANGE:
				if (m_lastPaddleHit)
					m_pickUp = m_pickUpGenerator.CreatePaddleSpeedChangePickUp(PLAYER1, PADDLESPEEDDIFFERENCE);
				else
					m_pickUp = m_pickUpGenerator.CreatePaddleSpeedChangePickUp(PLAYER2, PADDLESPEEDDIFFERENCE);
				m_pickUp.SetDirection(Vector2::down);
				m_pickUp.StartMoving();
				break;
			case Generator::BALLSIZECHANGE:
				if (m_switchBall)
					m_pickUp = m_pickUpGenerator.CreateBallSizeChangePickUp(BALL1, BALLSIZEDIFFERENCE);
				else
					m_pickUp = m_pickUpGenerator.CreateBallSizeChangePickUp(BALL2, BALLSIZEDIFFERENCE);
				break;
			case Generator::BALLSPEEDCHANGE:
				if (m_switchBall)
					m_pickUp = m_pickUpGenerator.CreateBallSpeedChangePickUp(BALL1, BALLSPEEDDIFFERENCE);
				else
					m_pickUp = m_pickUpGenerator.CreateBallSpeedChangePickUp(BALL2, BALLSPEEDDIFFERENCE);
				break;
			case Generator::BONUSPOINTS:
				if (m_switchBall)
					m_pickUp = m_pickUpGenerator.CreateBonusPointsPickUp(SCORE1, rand() % MAXSCOREDIFFERENCE + 1);
				else
					m_pickUp = m_pickUpGenerator.CreateBonusPointsPickUp(SCORE2, rand() % MAXSCOREDIFFERENCE + 1);
				break;
			case Generator::REMOVEPOINTS:
				if (m_switchBall)
					m_pickUp = m_pickUpGenerator.CreateRemovePointsPickUp(SCORE1, rand() % MAXSCOREDIFFERENCE + 1);
				else
					m_pickUp = m_pickUpGenerator.CreateRemovePointsPickUp(SCORE2, rand() % MAXSCOREDIFFERENCE + 1);
				break;
			default:
				m_isPickCreated = false;
				break;
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