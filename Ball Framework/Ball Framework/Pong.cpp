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
#define BRICKSPERCOLUMN 4
#define BRICKWIDTH 0.81f
#define BRICKHEIGHT 0.35f
#define BRICKLIMIT_X -1.5f
#define BRICKLIMIT_Y -3
#define BRICKSPACING 2

#define ACTIONTIME 5.0f
#define PICKUPSIZE 0.5f
#define PICKUPSPEEDCHANGE 2.0f

#define PLAYER          m_players[0] 
#define AIPLAYER        m_players[1] 
#define BALL            m_balls[0] 
#define PLAYER1SCORE    m_scores[0]
#define AISCORE         m_scores[1] 

constexpr auto WIDTHPADDLESPACING1 = -WIDTHUNITS / 2 + 1;
constexpr auto WIDTHPADDLESPACING2 = WIDTHUNITS / 2 - 1;
constexpr auto UPPERLIMIT = HEIGHTUNITS / 2;
constexpr auto LOWERLIMIT = -HEIGHTUNITS / 2;
constexpr auto LEFTLIMIT = -WIDTHUNITS / 2;
constexpr auto RIGHTLIMIT = WIDTHUNITS / 2;

#pragma endregion

	Pong::Pong(uint16_t width, uint16_t height, TTF_Font* font, const std::vector<std::string>& playersNames, uint32_t flags, uint16_t maxFPS)
		: BallGame("Pong", width, height, font, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),

		m_renderer{ nullptr },
		m_bricksNumber{ 0 },
		m_player1Name{ playersNames[0] }, m_AIName{ "A Certain Kind of Bot" },
		m_player1Score{ Colors::white }, m_AIScore{ Colors::white }
	{
		m_bricks = std::vector<std::vector<Brick>>{ BRICKCOLUMNS };
		m_playersStatistics = PlayersStatistics{ "..\\Assets\\statisticsPong.txt" };
		m_pauseButton = Button{ Vector2(LEFTLIMIT + 0.4f, UPPERLIMIT - 0.5f), 0.7f, 0.7f, Colors::black, Colors::white, "||" };
	}

	void Pong::Start()
	{
		InitializeBricks();

		m_players.emplace_back(Paddle(Vector2(WIDTHPADDLESPACING1, 0), PADDLEHEIGHT, PADDLEWIDTH, Vector2::up, Vector2::down, SDLK_w, SDLK_s, PADDLESPEED));
		m_players.emplace_back(Paddle(Vector2(WIDTHPADDLESPACING2, 0), PADDLEHEIGHT, PADDLEWIDTH, Vector2::up, Vector2::down, SDL_SCANCODE_LANG1, SDL_SCANCODE_LANG2, PADDLESPEED - 3.0f));

		m_balls.emplace_back(Ball(Vector2::zero, 0.5f, Vector2(pow(-1, (rand() % 2)), 0), 10.0f));
		std::cout << m_balls.size() << "\n";

		m_player1Score.SetText(MakeText(std::to_string(m_player1Score.GetScore()), Colors::white, m_buttonFont));
		m_player1Score.SetWidth(0.5f);
		m_player1Score.SetHeight(0.5f);
		m_player1Score.SetPosition(Vector2(2.0f, 4.0f));
		m_scores.push_back(m_player1Score);

		m_AIScore.SetText(MakeText(std::to_string(m_AIScore.GetScore()), Colors::white, m_buttonFont));
		m_AIScore.SetWidth(0.5f);
		m_AIScore.SetHeight(0.5f);
		m_AIScore.SetPosition(Vector2(-2, 4));
		m_scores.push_back(m_AIScore);

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

		m_pickUpGenerator.SetDefaultProperties(Vector2::up, PICKUPSIZE, PICKUPSPEEDCHANGE, ACTIONTIME);
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
		if (AIPLAYER.GetPosition().GetY() < LOWERLIMIT + AIPLAYER.GetHeight() / 2)
		{
			AIPLAYER.SetPosition(WIDTHPADDLESPACING2, LOWERLIMIT + AIPLAYER.GetHeight() / 2 + HEIGHTPADDLESPACING);
		}
		else if (AIPLAYER.GetPosition().GetY() > UPPERLIMIT - AIPLAYER.GetHeight() / 2)
		{
			AIPLAYER.SetPosition(WIDTHPADDLESPACING2, UPPERLIMIT - AIPLAYER.GetHeight() / 2 - HEIGHTPADDLESPACING);
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
		if (BALL.CheckCollision(PLAYER))
		{
			if (BALL.GetPosition().GetX() > PLAYER.GetPosition().GetX() + PLAYER.GetWidth() / 2)
			{
				float difference = (BALL.GetPosition().GetY() - PLAYER.GetPosition().GetY()) / 2;
				BALL.GetDirection().SetY(difference);
				LOGGING_INFO("Pong -> ball-player1 paddle collision");
			}
			else
			{
				if (BALL.GetPosition().GetY() > PLAYER.GetPosition().GetY())
					BALL.GetDirection().SetY(3);
				else
					BALL.GetDirection().SetY(-3);
			}
			BALL.GetDirection().GetX() *= -1;
			BALL.AddSpeed(0.25f);
			BALL.GetDirection().Normalize();
		}

		if (BALL.GetDirection().GetX() > 0 && BALL.GetPosition().GetX() > 1)
		{
			if (BALL.GetPosition().GetY() > AIPLAYER.GetPosition().GetY() + AIPLAYER.GetWidth() / 2)
			{
				AIPLAYER.SetDirection(Vector2::up);
				AIPLAYER.Move();
			}
			if (BALL.GetPosition().GetY() < AIPLAYER.GetPosition().GetY() - AIPLAYER.GetWidth() / 2)
			{
				AIPLAYER.SetDirection(Vector2::down);
				AIPLAYER.Move();
			}
		}

		if (BALL.CheckCollision(AIPLAYER))
		{
			if (BALL.GetPosition().GetX() < AIPLAYER.GetPosition().GetX() - AIPLAYER.GetWidth() / 2)
			{
				float difference = BALL.GetPosition().GetY() - AIPLAYER.GetPosition().GetY() / 2;
				BALL.GetDirection().SetY(difference);
				LOGGING_INFO("Pong -> ball-player1 paddle collision");
			}
			else
			{
				if (BALL.GetPosition().GetY() > AIPLAYER.GetPosition().GetY())
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
					if (m_isPickCreated == false)
						CreatePickUp(element->GetPosition());

					BALL.ChangeDirection(*element);
					row.erase(element);

					LOGGING_INFO("Pong -> ball-brick collision");

					--m_bricksNumber;

					if (m_bricksNumber < 1)
					{
						m_bricks.resize(BRICKCOLUMNS);
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
			PLAYER1SCORE.AddPoints(1);
			PLAYER1SCORE.SetText(MakeText(PLAYER1SCORE.ConvertToString(), Colors::white, m_buttonFont));
			Repaint();
			if (PLAYER1SCORE.GetScore() == 5)
			{
				m_playersStatistics.UpdateStatistics(m_player1Name, false);
				m_playersStatistics.UpdateStatistics(m_AIName, true);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", m_AIName.append("Player1 won!").c_str(), nullptr);
				Stop();
			}
			BALL.SetPosition(0, 0);
			BALL.SetDirection(-1, 0);
			BALL.SetSpeed(10);
		}
		else if (BALL.GetPosition().GetX() > RIGHTLIMIT)
		{
			AISCORE.AddPoints(1);
			AISCORE.SetText(MakeText(AISCORE.ConvertToString(), Colors::white, m_buttonFont));
			Repaint();
			if (AISCORE.GetScore() == 5)
			{
				m_playersStatistics.UpdateStatistics(m_player1Name, true);
				m_playersStatistics.UpdateStatistics(m_AIName, false);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", m_player1Name.append("Player2 won!").c_str(), nullptr);
				Stop();
			}
			BALL.SetPosition(0, 0);
			BALL.SetDirection(1, 0);
			BALL.SetSpeed(10);
		}
	}
#pragma endregion
	
	void Pong::Render(SDL_Renderer* renderer)
	{
		m_renderer = renderer;
		SDL_Rect aux;
		decltype(auto) scale = GetScale();

		SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
		scale.PointToPixel(aux, PLAYER.GetPosition(), PLAYER.GetWidth(), PLAYER.GetHeight());
		SDL_RenderFillRect(m_renderer, &aux);
		scale.PointToPixel(aux, AIPLAYER.GetPosition(), AIPLAYER.GetWidth(), AIPLAYER.GetHeight());
		SDL_RenderFillRect(m_renderer, &aux);

		uint16_t screenHeight = scale.GetScreenHeight();
		uint16_t screenCenter = scale.GetScreenWidth() / 2;
		for (int index = 0; index < screenHeight; index += 3)
		{
			SDL_RenderDrawPoint(m_renderer, screenCenter, index);
		}

		scale.PointToPixel(aux, BALL.GetPosition(), BALL.GetSize(), BALL.GetSize());
		SDL_RenderCopy(m_renderer, m_ballImage, nullptr, &aux);

		RenderPaddles(m_renderer);
		RenderBricks(m_renderer);
		RenderButton(m_renderer);
		RenderScore(m_renderer);

		if (m_isPickActive)
		{
			scale.PointToPixel(aux, m_pickUp.GetPosition(), m_pickUp.GetSize(), m_pickUp.GetSize());
			SDL_RenderCopy(m_renderer, m_pickUpImage, nullptr, &aux);
		}
	}

	void Pong::InitializeBricks()
	{
		float x = BRICKLIMIT_X, y = BRICKLIMIT_Y;

		for (auto&& row : m_bricks)
		{
			row.resize(rand() % 5);

			for (auto&& brick : row)
			{
				brick.Set(Vector2(x, y), BRICKHEIGHT, BRICKWIDTH);
				brick.SetColor(Colors::green);
				++m_bricksNumber;
				y += BRICKSPACING;
			}

			++x;
			y = BRICKLIMIT_Y;
		}
	}

	void Pong::CreatePickUp(const Vector2& position)
	{
		using Generator = PickUpGenerator::Actions;

		if ((rand() % 100) > 20)
		{
			m_isPickCreated = true;

			auto type = m_pickUpGenerator.GetPickUpType();
			LOGGING_INFO("BrickBreaker -> pick-up type is: {0}", static_cast<int>(type));

			switch (type)
			{
			case Generator::SPEEDCHANGE:
				m_pickUp = m_pickUpGenerator.CreateSpeedPickUp();
				break;
			case Generator::PADDLESIZECHANGE:
				m_pickUp = m_pickUpGenerator.CreatePaddleSizeChangePickUp(PLAYER, 1);
				m_pickUp.SetDirection(Vector2::left);
				m_pickUp.StartMoving();
				break;
			case Generator::PADDLESPEEDCHANGE:
				m_pickUp = m_pickUpGenerator.CreatePaddleSpeedChangePickUp(PLAYER, 10);
				m_pickUp.SetDirection(Vector2::left);
				m_pickUp.StartMoving();
				break;
			case Generator::BALLSIZECHANGE:
				m_pickUp = m_pickUpGenerator.CreateBallSizeChangePickUp(BALL, 1);
				break;
			case Generator::BALLSPEEDCHANGE:
				m_pickUp = m_pickUpGenerator.CreateBallSpeedChangePickUp(BALL, 5);
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