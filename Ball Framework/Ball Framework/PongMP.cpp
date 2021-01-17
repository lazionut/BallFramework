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
#define BRICKSPERCOLUMN 4
#define BRICKWIDTH 0.81f
#define BRICKHEIGHT 0.35f
#define BRICKLIMIT_X -1.5f
#define BRICKLIMIT_Y -3
#define BRICKSPACING 2

#define PLAYER1         m_players[0] 
#define PLAYER2         m_players[1] 
#define BALL            m_balls[0] 
#define PLAYER1SCORE    m_scores[0]
#define PLAYER2SCORE    m_scores[1] 

	constexpr auto WIDTHPADDLESPACING1 = -WIDTHUNITS / 2 + 1;
	constexpr auto WIDTHPADDLESPACING2 = WIDTHUNITS / 2 - 1;
	constexpr auto UPPERLIMIT = HEIGHTUNITS / 2;
	constexpr auto LOWERLIMIT = -HEIGHTUNITS / 2;
	constexpr auto LEFTLIMIT = -WIDTHUNITS / 2;
	constexpr auto RIGHTLIMIT = WIDTHUNITS / 2;

#pragma endregion

	PongMP::PongMP(uint16_t width, uint16_t height, TTF_Font* font, const std::vector<std::string>& playersNames, uint32_t flags, uint16_t maxFPS)
		: BallGame("Pong - Multiplayer", width, height, font, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),

		m_renderer{ nullptr },
		m_bricksNumber{ 0 },
		m_player1Name{ playersNames[0] }, m_player2Name{ playersNames[1] },
		m_player1Score{ Colors::white }, m_player2Score{ Colors::white }
	{
		m_lastTimeScale = Time::GetTimeScale();
		m_buttonFont = font;
		m_isPickCreated = false;
		m_isPickActive = false;
		m_isPaused = false;
		m_pickUpImage = nullptr;
		m_ballImage = nullptr;
		m_bricks = std::vector<std::vector<Brick>>{ BRICKCOLUMNS };
		m_playersStatistics = PlayersStatistics{ "..\\Assets\\statisticsPong.txt" };
		m_pauseButton = Button{ Vector2(LEFTLIMIT + 0.3f, UPPERLIMIT - 0.5f), 0.7f, 0.7f, Colors::black, Colors::white, "||" };
	}

	void PongMP::Start()
	{
		InitializeBricks();

		m_ballImage = LoadGameImage(Paths::ReturnObjectPath("ball"));
		m_pauseButton.SetText(MakeText(m_pauseButton.GetButtonText(), m_pauseButton.GetFontColor(), m_buttonFont));

		m_players.emplace_back(Paddle(Vector2(WIDTHPADDLESPACING1, 0), PADDLEHEIGHT, PADDLEWIDTH, Vector2::up, Vector2::down, SDLK_w, SDLK_s, PADDLESPEED));
		m_players.emplace_back(Paddle(Vector2(WIDTHPADDLESPACING2, 0), PADDLEHEIGHT, PADDLEWIDTH, Vector2::up, Vector2::down, SDLK_UP, SDLK_DOWN, PADDLESPEED));
		m_balls.emplace_back(Ball(Vector2::zero, 0.5f, Vector2(pow(-1, (rand() % 2)), 0), 10));

		m_player1Score.SetText(MakeText(std::to_string(m_player1Score.GetScore()), Colors::white, m_buttonFont));
		m_player2Score.SetText(MakeText(std::to_string(m_player2Score.GetScore()), Colors::white, m_buttonFont));
		m_scores.push_back(m_player1Score);
		m_scores.push_back(m_player2Score);

		if (m_ballImage == nullptr)
		{
			LOGGING_ERROR("PongMP -> ball image not found!");
			Stop();
			return;
		}

		m_pickUpImage = LoadGameImage(Paths::ReturnObjectPath("star"));
		if (m_pickUpImage == nullptr)
		{
			LOGGING_ERROR("PongMP -> pick-up image not found!");
			Stop();
			return;
		}

		m_pickUpGenerator.SetDefaultProperties(Vector2::up, 1.0f, 1.0f, 5.0f);
	}

	void PongMP::OnClose()
	{
		SDL_DestroyTexture(m_ballImage);
		SDL_DestroyTexture(m_pickUpImage);
		m_bricks.erase(m_bricks.begin(), m_bricks.end());
		Time::SetTimeScale(1.0f);
	}

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
			if (BALL.GetPosition().GetX() < PLAYER1.GetPosition().GetX() - PLAYER1.GetHeight() / 2
				&& BALL.GetPosition().GetX() > PLAYER1.GetPosition().GetX() + PLAYER1.GetHeight() / 2)
			{
				if (BALL.GetPosition().GetY() > PLAYER1.GetPosition().GetY())
					BALL.GetDirection().SetY(2);
				else
					BALL.GetDirection().SetY(-2);
			}
			else
			{
				float difference = BALL.GetPosition().GetY() - PLAYER1.GetPosition().GetY() / 2;
				BALL.GetDirection().SetY(difference);
				LOGGING_INFO("Pong -> ball-player1 paddle collision");
			}
			BALL.GetDirection().GetX() *= -1;
			BALL.AddSpeed(0.25f);
			BALL.GetDirection().Normalize();
		}
		else if (BALL.CheckCollision(PLAYER2))
		{
			if (BALL.GetPosition().GetX() < PLAYER2.GetPosition().GetX() - PLAYER2.GetHeight() / 2
				&& BALL.GetPosition().GetX() > PLAYER2.GetPosition().GetX() + PLAYER2.GetHeight() / 2)
			{
				if (BALL.GetPosition().GetY() > PLAYER2.GetPosition().GetY())
					BALL.GetDirection().SetY(2);
				else
					BALL.GetDirection().SetY(-2);
			}
			else
			{
				float difference = BALL.GetPosition().GetY() - PLAYER2.GetPosition().GetY() / 2;
				BALL.GetDirection().SetY(difference);
				LOGGING_INFO("Pong -> ball-player1 paddle collision");
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
					if (m_isPickCreated == false)
						CreatePickUp(element->GetPosition());

					BALL.ChangeDirection(*element);
					row.erase(element);

					LOGGING_INFO("PongMP -> ball-brick collision");

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

	void PongMP::CheckPickUpCollision()
	{
		if (m_isPickActive)
		{
			if (m_pickUp.IsMoving())
			{
				if (m_pickUp.CheckCollision(PLAYER1))
				{
					m_pickUp.InvokeAction();
					m_isPickActive = false;
					LOGGING_INFO("PongMP -> player1 paddle-pick-up collision");
				}
				else if (m_pickUp.CheckCollision(PLAYER2))
				{
					m_pickUp.InvokeAction();
					m_isPickActive = false;
					LOGGING_INFO("PongMP -> player2 paddle-pick-up collision");
				}
			}
			else
			{
				if (m_pickUp.CheckCollision(BALL))
				{
					m_pickUp.InvokeAction();
					m_isPickActive = false;
					LOGGING_INFO("PongMP -> ball-pick-up collision");
				}
			}
		}
	}

	void PongMP::CheckScoreCondition()
	{
		if (BALL.GetPosition().GetX() < LEFTLIMIT)
		{
			PLAYER1SCORE.AddPoints(1);
			PLAYER1SCORE.SetText(MakeText(PLAYER1SCORE.ConvertToString(), Colors::white, m_buttonFont));
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
			PLAYER2SCORE.SetText(MakeText(PLAYER2SCORE.ConvertToString(), Colors::white, m_buttonFont));
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

	void PongMP::Render(SDL_Renderer* renderer)
	{
		m_renderer = renderer;
		SDL_Rect aux;
		decltype(auto) scale = GetScale();

		SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
		scale.PointToPixel(aux, PLAYER1.GetPosition(), PLAYER1.GetWidth(), PLAYER1.GetHeight());
		SDL_RenderFillRect(m_renderer, &aux);
		scale.PointToPixel(aux, PLAYER2.GetPosition(), PLAYER2.GetWidth(), PLAYER2.GetHeight());
		SDL_RenderFillRect(m_renderer, &aux);

		uint16_t screenHeight = scale.GetScreenHeight();
		uint16_t screenCenter = scale.GetScreenWidth() / 2;
		for (int index = 0; index < screenHeight; index += 3)
		{
			SDL_RenderDrawPoint(m_renderer, screenCenter, index);
		}

		scale.PointToPixel(aux, BALL.GetPosition(), BALL.GetSize(), BALL.GetSize());
		SDL_RenderCopy(m_renderer, m_ballImage, nullptr, &aux);

		RenderBricks(m_renderer);
		RenderPlayersScore(m_renderer);
		RenderButton(m_renderer);

		if (m_isPickActive)
		{
			scale.PointToPixel(aux, m_pickUp.GetPosition(), m_pickUp.GetSize(), m_pickUp.GetSize());
			SDL_RenderCopy(m_renderer, m_pickUpImage, nullptr, &aux);
		}
	}

	void PongMP::InitializeBricks()
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

	void PongMP::CreatePickUp(const Vector2& position)
	{
		using Generator = PickUpGenerator::Actions;

		if (rand() % 100 > 60)
		{
			m_isPickCreated = true;
			auto random = rand() % 2;
			auto difference = 0.0f;

			auto type = m_pickUpGenerator.GetPickUpType();
			LOGGING_INFO("PongMP -> pick-up type is: {0}", static_cast<int>(type));

			switch (type)
			{
			case Generator::SPEEDCHANGE:
				m_pickUp = m_pickUpGenerator.CreateSpeedPickUp();
				m_pickUp.StartMoving();
				break;
			case Generator::PADDLESIZECHANGE:
				difference = 3;
				if (random)
				{
					m_pickUp = m_pickUpGenerator.CreatePaddleSizeChangePickUp(PLAYER1, difference);
					m_pickUp.SetDirection(PLAYER1.GetPosition() - position);
				}
				else
				{
					m_pickUp = m_pickUpGenerator.CreatePaddleSizeChangePickUp(PLAYER2, difference);
					m_pickUp.SetDirection(PLAYER1.GetPosition() - position);
				}
				m_pickUp.StartMoving();
				break;
			case Generator::PADDLESPEEDCHANGE:
				difference = 3;
				if (random)
				{
					m_pickUp = m_pickUpGenerator.CreatePaddleSpeedChangePickUp(PLAYER1, difference);
					m_pickUp.SetDirection(PLAYER1.GetPosition() - position);
				}
				else
				{
					m_pickUp = m_pickUpGenerator.CreatePaddleSpeedChangePickUp(PLAYER2, difference);
					m_pickUp.SetDirection(PLAYER1.GetPosition() - position);
				}
				m_pickUp.StartMoving();
				break;
			case Generator::BALLSIZECHANGE:
				m_pickUp = m_pickUpGenerator.CreateBallSizeChangePickUp(BALL, 2);
				break;
			case Generator::BALLSPEEDCHANGE:
				m_pickUp = m_pickUpGenerator.CreateBallSpeedChangePickUp(BALL, 2);
				break;
			case Generator::BONUSPOINTS:
				m_isPickActive = false;
				break;
			case Generator::REMOVEPOINTS:
				m_isPickActive = false;
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

	void PongMP::RenderPlayersScore(SDL_Renderer* renderer)
	{
		SDL_Rect aux1, aux2;
		decltype(auto) scale = GetScale();

		scale.PointToPixel(aux1, 2, 4, 0.5f, 0.5f);
		scale.PointToPixel(aux2, -2, 4, 0.5f, 0.5f);

		if (PLAYER1SCORE.GetText() != nullptr && PLAYER2SCORE.GetText() != nullptr)
		{
			SDL_RenderCopy(renderer, PLAYER1SCORE.GetText(), nullptr, &aux1);
			SDL_RenderCopy(renderer, PLAYER2SCORE.GetText(), nullptr, &aux2);
		}
		else
		{
			LOGGING_ERROR("PongMP -> font not found!");
		}
	}

}