#pragma once
#include <cstdint>
#include <string>
#include <SDL_ttf.h>î
#include <iostream>

class Score 
{
public:
	Score();
	void AddPoints(uint16_t points);
	uint16_t GetScore() const;
	std::string ConvertToString();

	SDL_Texture* GetText(SDL_Renderer* renderer);

private:
	uint16_t m_points;
};