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

void BallGame::RenderScore(SDL_Renderer* renderer)
{
	SDL_Rect aux1, aux2;
	decltype(auto) scale = GetScale();

	SDL_Texture* scoreTexture1 = m_score1.GetText(renderer);
	scale.PointToPixel(aux1, m_score1.GetPosition().GetX(), m_score1.GetPosition().GetY(), m_score1.GetWidth(), m_score1.GetHeight());
	if (m_score2.has_value())
	{
		SDL_Texture* scoreTexture2 = m_score2->GetText(renderer);
		scale.PointToPixel(aux2, m_score2->GetPosition().GetX(), m_score2->GetPosition().GetY(), m_score2->GetWidth(), m_score2->GetHeight());
		if (scoreTexture2 != nullptr)
		{
			SDL_RenderCopy(renderer, scoreTexture2, nullptr, &aux2);
			SDL_DestroyTexture(scoreTexture2);
		}
		else
		{
			std::cout << "Font was not loaded!" << std::endl;
		}
	}

	if (scoreTexture1 != nullptr)
	{
		SDL_RenderCopy(renderer, scoreTexture1, nullptr, &aux1);
		SDL_DestroyTexture(scoreTexture1);
	}
	else
	{
		std::cout << "Font was not loaded!" << std::endl;
	}
}
