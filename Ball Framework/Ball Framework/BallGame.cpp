#include "BallGame.h"

namespace BallFramework
{

	BallGame::BallGame(const std::string& title, uint16_t width, uint16_t height, TTF_Font* font, uint32_t flags, uint16_t maxFPS, uint16_t widthUnit, uint16_t heightUnit) :
		Game(title, width, height, flags, maxFPS, widthUnit, heightUnit),
		m_ballImage{ nullptr }, m_pickUpImage{ nullptr },
		m_isPickCreated{ false }, m_isPickActive{ false }, m_isPaused{ false },
		m_buttonFont{ font },
		m_playersStatistics{ "..\\Assets\\statisticsBB.txt" },
		m_lastTimeScale{ Time::GetTimeScale() } {}

	void BallGame::SetPlayers(const std::vector<std::string>& players)
	{
		m_playersNames = players;
	}

	void BallGame::Update()
	{
		for (auto&& player : m_players)
		{
			player.Move();
		}

		for (auto&& ball : m_balls)
		{
			ball.Move();
		}

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

#pragma region Input Methods

	void BallGame::KeyPressed(const SDL_Keycode& key)
	{
		if (!m_isPaused)
		{
			for (auto&& player : m_players)
			{
				player.KeyPressed(key);
			}
		}
	}

	void BallGame::KeyReleased(const SDL_Keycode& key)
	{
		if (key == SDLK_p || key == SDLK_ESCAPE)
		{
			Pause();
		}
		else if (!m_isPaused)
		{
			for (auto&& player : m_players)
			{
				player.KeyReleased(key);
			}
		}
	}

	void BallGame::MousePressed(const SDL_MouseButtonEvent& mouse)
	{
		IsMouseOnButton(mouse.x, mouse.y);
	}

	void BallGame::MouseReleased(const SDL_MouseButtonEvent& mouse)
	{
		if (IsMouseOnButton(mouse.x, mouse.y))
		{
			Pause();
		}
	}

#pragma endregion

#pragma region Render Methods

	void BallGame::RenderPaddles(SDL_Renderer* renderer)
	{
		SDL_Rect aux;
		decltype(auto) scale = GetScale();

		uint32_t index = 0;
		for (const auto& player : m_players)
		{
			auto [r, g, b, a] = m_paddleOutlines[index];
			SDL_SetRenderDrawColor(renderer, r, g, b, a);
			scale.PointToPixel(aux, player.GetPosition(),
				player.GetWidth() + m_outlineSizes[index], player.GetHeight() + m_outlineSizes[index]);
			SDL_RenderFillRect(renderer, &aux);
			++index;
		}

		index = 0;
		for (const auto& player : m_players)
		{
			SDL_SetRenderDrawColor(renderer, m_paddleColors[index].r, m_paddleColors[index].g, m_paddleColors[index].b, m_paddleColors[index].a);
			scale.PointToPixel(aux, player.GetPosition(), player.GetWidth(), player.GetHeight());
			SDL_RenderFillRect(renderer, &aux);
			++index;
		}
	}

	void BallGame::RenderGameObjects(SDL_Renderer* renderer)
	{
		SDL_Rect aux;
		decltype(auto) scale = GetScale();

		if (m_isPickActive)
		{
			scale.PointToPixel(aux, m_pickUp.GetPosition(), m_pickUp.GetSize(), m_pickUp.GetSize());
			SDL_RenderCopy(renderer, m_pickUpImage, nullptr, &aux);
		}

		uint32_t index = 0;
		for (const auto& ball : m_balls)
		{
			scale.PointToPixel(aux, ball.GameObject::GetPosition(), ball.GetSize(), ball.GetSize());
			SDL_RenderCopy(renderer, m_ballImages[index], nullptr, &aux);
			++index;
		}
	}

	void BallGame::RenderButton(SDL_Renderer* renderer)
	{
		SDL_Rect rect;
		decltype(auto) scale = GetScale();

		scale.PointToPixel(rect, m_pauseButton.GetPosition(), m_pauseButton.GetWidth(), m_pauseButton.GetHeight());
		m_pauseButton.SetRect(rect);
		scale.PointToPixel(rect, m_pauseButton.GetPosition(), m_pauseButton.GetWidth() - 0.2f, m_pauseButton.GetHeight());
		SDL_RenderCopy(renderer, m_pauseButton.GetText(), nullptr, &rect);
	}

	void BallGame::RenderBricks(SDL_Renderer* renderer)
	{
		SDL_Rect rect;
		decltype(auto) scale = GetScale();

		for (const auto& row : m_bricks)
		{
			for (const auto& brick : row)
			{
				auto [r, g, b, a] = brick.GetColor();
				SDL_SetRenderDrawColor(renderer, r, g, b, a);

				scale.PointToPixel(rect, brick.GetPosition(), brick.GetWidth(), brick.GetHeight());
				SDL_RenderFillRect(renderer, &rect);
			}
		}
	}

	void BallGame::RenderScore(SDL_Renderer* renderer)
	{
		SDL_Rect aux;
		SDL_Texture* scoreTexture;
		decltype(auto) scale = GetScale();

		for (auto& score : m_scores)
		{
			scoreTexture = score.GetText();

			if (scoreTexture == nullptr)
			{
				LOGGING_ERROR("Null score texture");
				continue;
			}
			if (score.GetScore() > 9 && score.GetWidth() < 1.0f) {
				score.SetWidth(score.GetWidth() * 2);
			}
			scale.PointToPixel(aux, score.GetPosition(), score.GetWidth(), score.GetHeight());
			SDL_RenderCopy(renderer, scoreTexture, nullptr, &aux);
		}
	}

#pragma endregion

	void BallGame::CheckPickUpCollision()
	{
		if (m_isPickActive)
		{
			if (m_pickUp.IsMoving())
			{
				for (const auto& paddle : m_players)
				{
					if (m_pickUp.CheckCollision(paddle))
					{
						m_pickUp.InvokeAction();
						m_isPickActive = false;
						LOGGING_INFO("BrickBreaker -> player paddle-pick-up collision");
					}
				}
			}
			else
			{
				for (const auto& ball : m_balls)
				{
					if (m_pickUp.CheckCollision(ball))
					{
						m_pickUp.InvokeAction();
						m_isPickActive = false;
						LOGGING_INFO("BrickBreaker -> ball-pick-up collision");
					}
				}
			}
		}
	}

	void BallGame::Pause()
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

	bool BallGame::IsMouseOnButton(Sint32 x, Sint32 y)
	{
		return (x > m_pauseButton.GetRect().x && x < m_pauseButton.GetRect().x + m_pauseButton.GetRect().w
			&& y > m_pauseButton.GetRect().y && y < m_pauseButton.GetRect().y + m_pauseButton.GetRect().h);
	}

}