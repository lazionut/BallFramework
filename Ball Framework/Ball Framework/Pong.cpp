#include "Pong.h"

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
#define ACTIONTIME 5.0f
#define PICKUPSIZE 0.5f
#define PICKUPSPEEDCHANGE 2.0f

#define PLAYER          m_players[0] 
#define BOT             m_players[1] 
#define BALL            m_balls[0] 
#define PLAYERSCORE    m_scores[0]
#define BOTSCORE         m_scores[1] 

constexpr auto WIDTHPADDLESPACING1 = -WIDTHUNITS / 2 + 1;
constexpr auto WIDTHPADDLESPACING2 = WIDTHUNITS / 2 - 1;
constexpr auto UPPERLIMIT = HEIGHTUNITS / 2;
constexpr auto LOWERLIMIT = -HEIGHTUNITS / 2;
constexpr auto LEFTLIMIT = -WIDTHUNITS / 2;
constexpr auto RIGHTLIMIT = WIDTHUNITS / 2;

#pragma endregion

	Pong::Pong(uint16_t width, uint16_t height, TTF_Font* font, const std::vector<std::string>& playersNames, uint32_t flags, uint16_t maxFPS)
		: BallGame("Pong", width, height, font, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),

		m_bricksNumber{ 0 },
		m_playerName{ playersNames[0] }, m_botName{ "A Certain Kind of Bot" }
	{
		m_bricks = std::vector<std::vector<Brick>>{ BRICKCOLUMNS };
		m_playersStatistics = PlayersStatistics{ "..\\Assets\\statisticsPong.txt" };
		m_pauseButton = Button{ Vector2(LEFTLIMIT + 0.4f, UPPERLIMIT - 0.5f), 0.7f, 0.7f, Colors::black, Colors::white, "||" };
	}

	void Pong::Start()
	{
		SetBackgroundColor({ 7, 62, 95, 255 });

		InitializeBricks();

		m_players.emplace_back(Paddle(Vector2(WIDTHPADDLESPACING1, 0), PADDLEHEIGHT, PADDLEWIDTH, Vector2::up, Vector2::down, SDLK_w, SDLK_s, PADDLESPEED));
		m_players.emplace_back(Paddle(Vector2(WIDTHPADDLESPACING2, 0), PADDLEHEIGHT, PADDLEWIDTH, Vector2::up, Vector2::down, SDL_SCANCODE_LANG1, SDL_SCANCODE_LANG2, PADDLESPEED - 3.0f));
		m_balls.emplace_back(Ball(Vector2::zero, 0.5f, Vector2(pow(-1, Random::Range(2)), 0), 10.0f));

		InitializeScore();

		m_pauseButton.SetText(MakeText(m_pauseButton.GetButtonText(), m_pauseButton.GetFontColor(), m_buttonFont));

		m_ballImage = LoadGameImage(Paths::ReturnObjectPath("ball"));
		m_ballImages.push_back(m_ballImage);
		if (m_ballImage == nullptr)
		{
			LOGGING_ERROR("Pong -> ball image not found!");
			Stop();
			return;
		}

		m_pickUpImage = LoadGameImage(Paths::ReturnObjectPath("star"));
		if (m_pickUpImage == nullptr)
		{
			LOGGING_ERROR("Pong -> pick-up image not found!");
			Stop();
			return;
		}

		m_paddleColors.push_back(Colors::green);
		m_paddleOutlines.push_back(Colors::dark_green);
		m_outlineSizes.push_back(0.1f);

		m_paddleColors.push_back(Colors::green);
		m_paddleOutlines.push_back(Colors::dark_green);
		m_outlineSizes.push_back(0.1f);

		m_pickUpGenerator.SetPickUpDefaultProperties(Vector2::up, PICKUPSIZE, PICKUPSPEEDCHANGE, ACTIONTIME);
	}

	void Pong::OnClose()
	{
		SDL_DestroyTexture(m_ballImage);
		SDL_DestroyTexture(m_pickUpImage);
		m_bricks.erase(m_bricks.begin(), m_bricks.end());
		Time::SetTimeScale(1.0f);
	}

#pragma region Collision Methods
	void Pong::CheckCollision()
	{
		CheckPickUpCollision();
		CheckPaddleWallCollision();
		CheckBallWallCollision();
		CheckBallPaddleCollision();
		CheckBallBrickCollision();
		CheckScoreCondition();

		CheckBotMovement();
	}

	void Pong::CheckPaddleWallCollision()
	{
		if (PLAYER.GetPosition().GetY() < LOWERLIMIT + PLAYER.GetHeight() / 2)
		{
			PLAYER.SetPosition(WIDTHPADDLESPACING1, LOWERLIMIT + PLAYER.GetHeight() / 2 + HEIGHTPADDLESPACING);
		}
		else if (PLAYER.GetPosition().GetY() > UPPERLIMIT - PLAYER.GetHeight() / 2)
		{
			PLAYER.SetPosition(WIDTHPADDLESPACING1, UPPERLIMIT - PLAYER.GetHeight() / 2 - HEIGHTPADDLESPACING);
		}
		if (BOT.GetPosition().GetY() < LOWERLIMIT + BOT.GetHeight() / 2)
		{
			BOT.SetPosition(WIDTHPADDLESPACING2, LOWERLIMIT + BOT.GetHeight() / 2 + HEIGHTPADDLESPACING);
		}
		else if (BOT.GetPosition().GetY() > UPPERLIMIT - BOT.GetHeight() / 2)
		{
			BOT.SetPosition(WIDTHPADDLESPACING2, UPPERLIMIT - BOT.GetHeight() / 2 - HEIGHTPADDLESPACING);
		}
	}

	void Pong::CheckBallWallCollision()
	{
		if (BALL.GetPosition().GetY() + BALL.GetSize() / 2 > UPPERLIMIT)
		{
			BALL.GetPosition().SetY(UPPERLIMIT - BALL.GetSize() / 2);
			BALL.GetDirection().GetY() *= -1;
			LOGGING_INFO("Pong -> ball-upper wall collision");
		}
		else if (BALL.GetPosition().GetY() - BALL.GetSize() / 2 < LOWERLIMIT)
		{
			BALL.GetPosition().SetY(LOWERLIMIT + BALL.GetSize() / 2);
			BALL.GetDirection().GetY() *= -1;
			LOGGING_INFO("Pong -> ball-lower wall collision");
		}
	}

	void Pong::CheckBallPaddleCollision()
	{
		if (BALL.GetDirection().GetX() < 0 && BALL.CheckCollision(PLAYER))
		{
			if (BALL.GetPosition().GetX() > PLAYER.GetPosition().GetX() + PLAYER.GetWidth() / 2)
			{
				float difference = (BALL.GetPosition().GetY() - PLAYER.GetPosition().GetY()) / 3;
				BALL.GetDirection().SetY(difference);
				LOGGING_INFO("Pong -> ball-player1 paddle collision");
			}
			else
			{
				if (BALL.GetPosition().GetY() > PLAYER.GetPosition().GetY())
					BALL.GetDirection().SetY(1);
				else
					BALL.GetDirection().SetY(-1);
			}
			BALL.GetDirection().GetX() *= -1;
			BALL.AddSpeed(0.25f);
			BALL.GetDirection().Normalize();
		}

		if (BALL.GetDirection().GetX() > 0 && BALL.CheckCollision(BOT))
		{
			if (BALL.GetPosition().GetX() < BOT.GetPosition().GetX() - BOT.GetWidth() / 2)
			{
				float difference = BALL.GetPosition().GetY() - BOT.GetPosition().GetY() / 3;
				BALL.GetDirection().SetY(difference);
				LOGGING_INFO("Pong -> ball-player1 paddle collision");
			}
			else
			{
				if (BALL.GetPosition().GetY() > BOT.GetPosition().GetY())
					BALL.GetDirection().SetY(3);
				else
					BALL.GetDirection().SetY(-3);
			}
			BALL.GetDirection().GetX() *= -1;
			BALL.AddSpeed(0.25f);
			BALL.GetDirection().Normalize();
		}
	}

	void Pong::CheckBallBrickCollision()
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

					LOGGING_INFO("Pong -> ball-brick collision");

					--m_bricksNumber;

					if (m_bricksNumber < 1)
					{
						m_bricks.resize(rand() % 5);
						InitializeBricks();
					}

					return;
				}
			}
		}
	}

	void Pong::CheckScoreCondition()
	{
		if (BALL.GetPosition().GetX() < LEFTLIMIT)
		{
			PLAYERSCORE.AddPoints(1);
			PLAYERSCORE.SetText(MakeText(PLAYERSCORE.ConvertToString(), Colors::white, m_buttonFont));
			Repaint();
			if (PLAYERSCORE.GetScore() == 5)
			{
				m_playersStatistics.UpdateStatistics(m_playerName, false);
				m_playersStatistics.UpdateStatistics(m_botName, true);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", m_botName.append(" won!").c_str(), nullptr);
				Stop();
			}
			BALL.SetPosition(0, 0);
			BALL.SetDirection(-1, 0);
			BALL.SetSpeed(10);
		}
		else if (BALL.GetPosition().GetX() > RIGHTLIMIT)
		{
			BOTSCORE.AddPoints(1);
			BOTSCORE.SetText(MakeText(BOTSCORE.ConvertToString(), Colors::white, m_buttonFont));
			Repaint();
			if (BOTSCORE.GetScore() == 5)
			{
				m_playersStatistics.UpdateStatistics(m_playerName, true);
				m_playersStatistics.UpdateStatistics(m_botName, false);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", m_playerName.append(" won!").c_str(), nullptr);
				Stop();
			}
			BALL.SetPosition(0, 0);
			BALL.SetDirection(1, 0);
			BALL.SetSpeed(10);
		}
	}
#pragma endregion

	void Pong::CheckBotMovement()
	{
		if (BALL.GetDirection().GetX() > 0 && BALL.GetX() > 1)
		{
			if (BALL.GetY() > BOT.GetY() + BOT.GetWidth() / 2)
			{
				BOT.SetDirection(Vector2::up);
				BOT.Move();
			}
			if (BALL.GetY() < BOT.GetY() - BOT.GetWidth() / 2)
			{
				BOT.SetDirection(Vector2::down);
				BOT.Move();
			}
		}
	}

	void Pong::Render(SDL_Renderer* renderer)
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

	void Pong::InitializeBricks()
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
	}

	void Pong::InitializeScore()
	{
		Score score{ Colors::white };

		score.SetSize(0.5f, 0.5f);
		score.SetPosition(Vector2(2.0f, 4.0f));
		m_scores.push_back(score);
		m_scores.back().SetText(MakeText(score.ConvertToString(), Colors::white, m_buttonFont));

		score.SetSize(0.5f, 0.5f);
		score.SetPosition(Vector2(-2.0f, 4.0f));
		m_scores.push_back(score);
		m_scores.back().SetText(MakeText(score.ConvertToString(), Colors::white, m_buttonFont));
	}

	void Pong::CreatePickUp(const Vector2& position)
	{
		if (Random::Range(100) > PICKUPSPAWNCHANCE)
		{
			m_pickUp.SetActive(true);

			auto type = m_pickUpGenerator.GetPickUpType();
			LOGGING_INFO("BrickBreaker -> pick-up type is: {0}", static_cast<int>(type));

			switch (type)
			{
			case Actions::SPEEDCHANGE:
				m_pickUp = m_pickUpGenerator.CreateSpeedPickUp();
				break;
			case Actions::PADDLESIZECHANGE:
				m_pickUp = m_pickUpGenerator.CreatePaddleSizeChangePickUp(PLAYER, 1);
				m_pickUp.SetDirection(Vector2::left);
				m_pickUp.StartMoving();
				break;
			case Actions::PADDLESPEEDCHANGE:
				m_pickUp = m_pickUpGenerator.CreatePaddleSpeedChangePickUp(PLAYER, 10);
				m_pickUp.SetDirection(Vector2::left);
				m_pickUp.StartMoving();
				break;
			case Actions::BALLSIZECHANGE:
				m_pickUp = m_pickUpGenerator.CreateBallSizeChangePickUp(BALL, 1);
				break;
			case Actions::BALLSPEEDCHANGE:
				m_pickUp = m_pickUpGenerator.CreateBallSpeedChangePickUp(BALL, 5);
				break;
			default:
				m_pickUp.SetActive(false);
				return;
			}

			m_pickUp.SetPosition(position);
			m_pickUp.SetVisible(true);
		}
		else
		{
			m_pickUp.SetActive(false);
		}
	}

}