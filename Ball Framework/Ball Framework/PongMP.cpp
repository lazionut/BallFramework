#include "PongMP.h"

namespace BallFramework
{

#pragma region CONSTANTS

#define WIDTHUNITS 20
#define HEIGHTUNITS 10
#define PADDLEWIDTH 3.0f
#define PADDLEHEIGHT 0.5f
#define HEIGHTPADDLESPACING 0.010f
#define PADDLESPEED 6.0f
#define BRICKCOLUMNS 4
#define BRICKWIDTH 0.81f
#define BRICKHEIGHT 0.35f
#define BRICKLIMIT_X -1.5f
#define BRICKLIMIT_Y -3
#define BRICKSPACING 2
#define MAXBRICKSONROW 4

#define PICKUPSPAWNCHANCE 70

#define PLAYER1         m_players[0] 
#define PLAYER2         m_players[1] 
#define BALL            m_balls[0] 
#define PLAYER1SCORE    m_scores[0]
#define PLAYER2SCORE    m_scores[1] 
#define BALLIMAGE		m_balls[0].GetImage() 

	constexpr auto WIDTHPADDLESPACING1 = -WIDTHUNITS / 2 + 1;
	constexpr auto WIDTHPADDLESPACING2 = WIDTHUNITS / 2 - 1;
	constexpr auto UPPERLIMIT = HEIGHTUNITS / 2;
	constexpr auto LOWERLIMIT = -HEIGHTUNITS / 2;
	constexpr auto LEFTLIMIT = -WIDTHUNITS / 2;
	constexpr auto RIGHTLIMIT = WIDTHUNITS / 2;

#pragma endregion

	PongMP::PongMP(uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
		: BallGame("Pong - Multiplayer", width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),
		m_bricksNumber{ 0 }
	{
		m_bricks = std::vector<std::vector<Brick>>{ BRICKCOLUMNS };
		m_playersStatistics = PlayersStatistics{ "..\\Assets\\statisticsPongMP.txt" };
		m_pauseButton = Button{ Vector2(LEFTLIMIT + 0.4f, UPPERLIMIT - 0.5f), 0.7f, 0.7f, Colors::black, Colors::white, "||" };
	}

	void PongMP::Start()
	{
		SetBackgroundColor({ 7, 62, 95, 255 });

		InitializeBricks();
		InitializeScore();
		InitializePongMPObjects();
		LoadPongMPImages();
		m_pickUpGenerator.SetPickUpDefaultProperties(Vector2::up, 1.0f, 1.0f, 5.0f);
	}

	void PongMP::OnClose()
	{
		SDL_DestroyTexture(BALLIMAGE);
		SDL_DestroyTexture(m_pickUpImage);
		m_bricks.erase(m_bricks.begin(), m_bricks.end());
		Time::SetTimeScale(1.0f);
	}

#pragma region Collision Methods
	void PongMP::CheckCollision()
	{
		CheckPaddleWallCollision();
		CheckBallWallCollision();
		CheckBallPaddleCollision();
		CheckBallBrickCollision();
		CheckPickUpCollision();
		CheckScoreCondition();
	}

	void PongMP::CheckPaddleWallCollision()
	{
		if (PLAYER1.GetPosition().GetY() < LOWERLIMIT + PLAYER1.GetHeight() / 2)
		{
			PLAYER1.SetPosition(WIDTHPADDLESPACING1, LOWERLIMIT + PLAYER1.GetHeight() / 2 + HEIGHTPADDLESPACING);
		}
		else if (PLAYER1.GetPosition().GetY() > UPPERLIMIT - PLAYER1.GetHeight() / 2)
		{
			PLAYER1.SetPosition(WIDTHPADDLESPACING1, UPPERLIMIT - PLAYER1.GetHeight() / 2 - HEIGHTPADDLESPACING);
		}
		if (PLAYER2.GetPosition().GetY() < LOWERLIMIT + PLAYER2.GetHeight() / 2)
		{
			PLAYER2.SetPosition(WIDTHPADDLESPACING2, LOWERLIMIT + PLAYER2.GetHeight() / 2 + HEIGHTPADDLESPACING);
		}
		else if (PLAYER2.GetPosition().GetY() > UPPERLIMIT - PLAYER2.GetHeight() / 2)
		{
			PLAYER2.SetPosition(WIDTHPADDLESPACING2, UPPERLIMIT - PLAYER2.GetHeight() / 2 - HEIGHTPADDLESPACING);
		}
	}

	void PongMP::CheckBallWallCollision()
	{
		if (BALL.GetPosition().GetY() + BALL.GetSize() / 2 > UPPERLIMIT)
		{
			BALL.GetPosition().SetY(UPPERLIMIT - BALL.GetSize() / 2);
			BALL.GetDirection().GetY() *= -1;
			LOGGING_INFO("PongMP -> ball-upper wall collision");
		}
		else if (BALL.GetPosition().GetY() - BALL.GetSize() / 2 < LOWERLIMIT)
		{
			BALL.GetPosition().SetY(LOWERLIMIT + BALL.GetSize() / 2);
			BALL.GetDirection().GetY() *= -1;
			LOGGING_INFO("PongMP -> ball-lower wall collision");
		}
	}

	void PongMP::CheckBallPaddleCollision()
	{
		if (BALL.CheckCollision(PLAYER1))
		{
			if (BALL.GetPosition().GetX() > PLAYER1.GetPosition().GetX() + PLAYER1.GetWidth() / 2)
			{
				float difference = (BALL.GetPosition().GetY() - PLAYER1.GetPosition().GetY()) / 2;
				BALL.GetDirection().SetY(difference);
				LOGGING_INFO("Pong -> ball-player1 paddle collision");
			}
			else
			{
				if (BALL.GetPosition().GetY() > PLAYER1.GetPosition().GetY())
					BALL.GetDirection().SetY(3);
				else
					BALL.GetDirection().SetY(-3);
			}
			BALL.GetDirection().GetX() *= -1;
			BALL.AddSpeed(0.25f);
			BALL.GetDirection().Normalize();
		}
		else if (BALL.CheckCollision(PLAYER2))
		{
			if (BALL.GetPosition().GetX() < PLAYER2.GetPosition().GetX() - PLAYER2.GetWidth() / 2)
			{
				float difference = (BALL.GetPosition().GetY() - PLAYER2.GetPosition().GetY()) / 2;
				BALL.GetDirection().SetY(difference);
				LOGGING_INFO("Pong -> ball-player1 paddle collision");
			}
			else
			{
				if (BALL.GetPosition().GetY() > PLAYER2.GetPosition().GetY())
					BALL.GetDirection().SetY(3);
				else
					BALL.GetDirection().SetY(-3);
			}
			BALL.GetDirection().GetX() *= -1;
			BALL.AddSpeed(0.25f);
			BALL.GetDirection().Normalize();
		}
	}

	void PongMP::CheckBallBrickCollision()
	{
		for (auto& row : m_bricks)
		{
			for (auto element = row.begin(); element < row.end(); ++element)
			{
				if (BALL.CheckCollision(*element))
				{
					if (!m_pickUp.IsActive())
					{
						CreatePickUp(element->GetPosition());
					}

					BALL.ChangeDirection(*element);
					row.erase(element);

					LOGGING_INFO("PongMP -> ball-brick collision");

					--m_bricksNumber;

					if (m_bricksNumber < 1)
					{
						m_bricks.resize(Random::Range(1, 5));
						InitializeBricks();
					}

					return;
				}
			}
		}
	}

	void PongMP::CheckScoreCondition()
	{
		if (BALL.GetPosition().GetX() < LEFTLIMIT)
		{
			PLAYER1SCORE.AddPoints(1);
			PLAYER1SCORE.SetText(MakeText(PLAYER1SCORE.ConvertToString(), PLAYER1SCORE.GetScoreColor()));
			Repaint();
			if (PLAYER1SCORE.GetScore() == 5)
			{
				m_playersStatistics.UpdateStatistics(m_player1Name, false);
				m_playersStatistics.UpdateStatistics(m_player2Name, true);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", m_player2Name.append(" won!").c_str(), nullptr);
				Stop();
			}
			BALL.SetPosition(0, 0);
			BALL.SetDirection(-1, 0);
			BALL.SetSpeed(10);
		}
		else if (BALL.GetPosition().GetX() > RIGHTLIMIT)
		{
			PLAYER2SCORE.AddPoints(1);
			PLAYER2SCORE.SetText(MakeText(PLAYER2SCORE.ConvertToString(), PLAYER2SCORE.GetScoreColor()));
			Repaint();
			if (PLAYER2SCORE.GetScore() == 5)
			{
				m_playersStatistics.UpdateStatistics(m_player1Name, true);
				m_playersStatistics.UpdateStatistics(m_player2Name, false);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", m_player1Name.append(" won!").c_str(), nullptr);
				Stop();
			}
			BALL.SetPosition(0, 0);
			BALL.SetDirection(1, 0);
			BALL.SetSpeed(10);
		}
	}
#pragma endregion

#pragma region Rendering Methods
	void PongMP::Render(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		uint16_t screenHeight = GetScale().GetScreenHeight();
		uint16_t screenCenter = GetScale().GetScreenWidth() / 2;
		for (int index = 0; index < screenHeight; index += 3)
		{
			SDL_RenderDrawPoint(renderer, screenCenter, index);
		}

		RenderGameObjects(renderer);
		RenderPaddles(renderer);
		RenderBricks(renderer);
		RenderButton(renderer);
		RenderScore(renderer);
	}

#pragma endregion

	void PongMP::InitializeBricks()
	{
		float x = BRICKLIMIT_X, y = BRICKLIMIT_Y;
		Brick temp;

		for (auto&& row : m_bricks)
		{
			for (int i = 0; i < MAXBRICKSONROW; ++i)
			{
				if (Random::CoinFlip())
				{
					temp.Set(Vector2(x, y), BRICKHEIGHT, BRICKWIDTH);
					temp.SetColor(Colors::green);
					row.push_back(temp);

					++m_bricksNumber;
					LOGGING_INFO("Brick created");
				}

				y += BRICKSPACING;
			}

			++x;
			y = BRICKLIMIT_Y;
		}

		if (!m_bricksNumber)
		{
			InitializeBricks();
		}
	}

	void PongMP::InitializeScore()
	{
		Score score{ Colors::white };

		score.SetSize(0.5f, 0.5f);
		score.SetPosition(Vector2(2.0f, 4.0f));
		m_scores.push_back(score);
		m_scores.back().SetText(MakeText(score.ConvertToString(), score.GetScoreColor()));

		score.SetSize(0.5f, 0.5f);
		score.SetPosition(Vector2(-2.0f, 4.0f));
		m_scores.push_back(score);
		m_scores.back().SetText(MakeText(score.ConvertToString(), score.GetScoreColor()));
	}

	void PongMP::InitializePongMPObjects()
	{
		m_players.emplace_back(Paddle(Vector2(WIDTHPADDLESPACING1, 0), PADDLEHEIGHT, PADDLEWIDTH, Vector2::up, Vector2::down, SDLK_w, SDLK_s, PADDLESPEED));
		m_players.emplace_back(Paddle(Vector2(WIDTHPADDLESPACING2, 0), PADDLEHEIGHT, PADDLEWIDTH, Vector2::up, Vector2::down, SDLK_UP, SDLK_DOWN, PADDLESPEED));

		m_paddleColors.push_back(Colors::green);
		m_paddleOutlines.push_back(Colors::dark_green);
		m_outlineSizes.push_back(0.1f);

		m_paddleColors.push_back(Colors::green);
		m_paddleOutlines.push_back(Colors::dark_green);
		m_outlineSizes.push_back(0.1f);

		m_balls.emplace_back(Ball(Vector2::zero, 0.5f, Vector2(pow(-1, Random::Range(2)), 0), 10));

		m_pauseButton.SetText(MakeText(m_pauseButton.GetButtonText(), m_pauseButton.GetFontColor()));

		m_player1Name = m_playersNames.front();
		m_player2Name = m_playersNames.back();
	}

	void PongMP::LoadPongMPImages()
	{
		BALL.SetImage(LoadGameImage(Paths::ReturnObjectPath("ball")));
		m_pickUpImage = LoadGameImage(Paths::ReturnObjectPath("star"));

		if (BALLIMAGE == nullptr)
		{
			LOGGING_ERROR("PongMP -> ball image not found!");
			Stop();
			return;
		}
		if (m_pickUpImage == nullptr)
		{
			LOGGING_ERROR("PongMP -> pick-up image not found!");
			Stop();
			return;
		}
	}

	void PongMP::CreatePickUp(const Vector2& position)
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
				if (Random::CoinFlip())
				{
					m_pickUp.SetDirection(Vector2::left);
				}
				else
				{
					m_pickUp.SetDirection(Vector2::right);
				}
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

			/*	m_pickUp.SetPosition(position);
				m_pickUp.SetVisible(true);*/
		}
		else
		{
			m_pickUp.SetActive(false);
		}
	}

}