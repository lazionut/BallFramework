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

