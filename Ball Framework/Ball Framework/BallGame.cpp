#include "BallGame.h"

namespace BallFramework
{

	BallGame::BallGame(const std::string& title, uint16_t width, uint16_t height, TTF_Font* font, uint32_t flags, uint16_t maxFPS, uint16_t widthUnit, uint16_t heightUnit) :
		Game(title, width, height, flags, maxFPS, widthUnit, heightUnit),
		m_ballImage{ nullptr },
		m_pickUpImage{ nullptr }, m_isPickCreated{ false }, m_isPickActive{ false },
		m_buttonFont{ font },
		m_isPaused{ false },
		m_playersStatistics{ "..\\Assets\\statisticsBB.txt" }
	{
		m_lastTimeScale = Time::GetTimeScale();
	}

	void BallGame::Update()
	{
		for (auto&& player : m_playerList)
		{
			player.Move();
		}

		for (auto&& ball : m_ballList)
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

	void BallGame::KeyPressed(const SDL_Keycode& key)
	{
		if (!m_isPaused)
		{
			for (auto&& player : m_playerList)
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
			for (auto&& player : m_playerList)
			{
				player.KeyReleased(key);
			}
		}
	}

	void BallGame::MousePressed(const SDL_MouseButtonEvent& mouse)
	{
		IsMouseInButtonBounds(mouse.x, mouse.y);
	}

	void BallGame::MouseReleased(const SDL_MouseButtonEvent& mouse)
	{
		if (IsMouseInButtonBounds(mouse.x, mouse.y))
		{
			Pause();
		}
	}

	void BallGame::Render(SDL_Renderer* renderer)
	{
		SDL_Rect aux;
		decltype(auto) scale = GetScale();

		RenderButton(renderer);

		auto&& [r, g, b, a] = m_color;

		SDL_SetRenderDrawColor(renderer, r, g, b, a);

		for (const auto& player : m_playerList)
		{
			scale.PointToPixel(aux, player.GetPosition(), player.GetWidth(), player.GetHeight());
			SDL_RenderFillRect(renderer, &aux);
		}

		for (const auto& ball : m_ballList)
		{
			scale.PointToPixel(aux, ball.GetPosition(), ball.GetSize(), ball.GetSize());
			SDL_RenderCopy(renderer, m_ballImage, nullptr, &aux);
		}

		RenderScore(renderer);
		RenderBricks(renderer);

		if (m_isPickActive)
		{
			scale.PointToPixel(aux, m_pickUp.GetPosition(), m_pickUp.GetSize(), m_pickUp.GetSize()); //pickup
			SDL_RenderCopy(renderer, m_pickUpImage, nullptr, &aux);
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

	void BallGame::RenderButton(SDL_Renderer* renderer)
	{
		SDL_Rect rect;
		decltype(auto) scale = GetScale();

		scale.PointToPixel(rect, m_pauseButton.GetPosition(), m_pauseButton.GetWidth(), m_pauseButton.GetHeight());
		m_pauseButton.SetRect(rect);
		scale.PointToPixel(rect, m_pauseButton.GetPosition(), m_pauseButton.GetWidth() - 0.2f, m_pauseButton.GetHeight());
		SDL_RenderCopy(renderer, m_pauseButton.GetText(), nullptr, &rect);
	}

	bool BallGame::IsMouseInButtonBounds(Sint32 x, Sint32 y)
	{
		return (x > m_pauseButton.GetRect().x && x < m_pauseButton.GetRect().x + m_pauseButton.GetRect().w
			&& y > m_pauseButton.GetRect().y && y < m_pauseButton.GetRect().y + m_pauseButton.GetRect().h);
	}

	void BallGame::RenderBricks(SDL_Renderer* renderer)
	{
		SDL_Rect rect;
		decltype(auto) scale = GetScale();
		for (const auto& rowIterator : m_bricks)
			for (const auto& columnIterator : rowIterator)
			{
				scale.PointToPixel(rect, columnIterator.GetPosition(), columnIterator.GetHeight(), columnIterator.GetWidth());
				SDL_RenderFillRect(renderer, &rect);
			}
	}

	void BallGame::RenderScore(SDL_Renderer* renderer)
	{
		SDL_Rect aux;
		decltype(auto) scale = GetScale();

		SDL_Texture* scoreTexture;
		for (const auto& score : m_scoreList)
		{
			scoreTexture = score.GetText();

			if (scoreTexture == nullptr)
			{
				LOGGING_ERROR("Null score texture");
				continue;
			}

			scale.PointToPixel(aux, score.GetPosition().GetX(), score.GetPosition().GetY(), score.GetWidth(), score.GetHeight());
			SDL_RenderCopy(renderer, scoreTexture, nullptr, &aux);
		}
	}
}