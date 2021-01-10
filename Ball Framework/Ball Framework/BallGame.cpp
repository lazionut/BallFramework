#include "BallGame.h"


BallGame::BallGame(const std::string& title, uint16_t width, uint16_t height, TTF_Font* font, uint32_t flags, uint16_t maxFPS, uint16_t widthUnit, uint16_t heightUnit) :
	Game(title, width, height, flags, maxFPS, widthUnit, heightUnit),
	m_renderer{ nullptr },
	m_ballImage{ nullptr },
	m_score1{ font },
	m_pickUpImage{ nullptr }, m_isPickCreated{ false }, m_isPickActive{ false },
	m_buttonFont{ font },
	m_isPaused{ false },
	m_playersStatistics{ "..\\Assets\\statisticsBB.txt" }
{
	m_lastTimeScale = Time::GetTimeScale();
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
