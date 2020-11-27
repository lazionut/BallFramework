#include "Score.h"

void Score::AddPoints(uint16_t gameScore)
{
	gameScore += m_points;
}

uint16_t Score::GetScore() const
{
	return m_points;
}

std::string Score::ConvertToString()
{
	return std::to_string(m_points);
}