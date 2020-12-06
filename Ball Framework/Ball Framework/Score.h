#pragma 
#include "Game.h"
#include <cstdint>
#include <string>

class Score 
{
public:
	void AddPoints(uint16_t gameScore);

	uint16_t GetScore() const;
	
	std::string ConvertToString();

private:
	uint16_t m_points;
};