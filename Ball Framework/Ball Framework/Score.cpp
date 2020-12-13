#include "Score.h"

Score::Score(TTF_Font* font) :
	m_font{ font }
{
	m_points = 0;
}

void Score::AddPoints(uint16_t points)
{
	m_points += points;
}

uint16_t Score::GetScore() const
{
	return m_points;
}

std::string Score::ConvertToString()
{
	return std::to_string(m_points);
}

SDL_Texture* Score::GetText(SDL_Renderer* renderer)
{
	SDL_Color white = { 255, 255, 255 };
	SDL_Surface* loadedText = TTF_RenderText_Solid(m_font, ConvertToString().c_str(), white);

	if (loadedText)
	{
		SDL_Texture* result = SDL_CreateTextureFromSurface(renderer, loadedText);
		SDL_FreeSurface(loadedText);
		return result;
	}
}