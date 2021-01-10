#include "Score.h"

Score::Score(TTF_Font* font) :
	m_font{ font },
	m_position {Vector2::zero},
	m_width{ 0 }, m_height{ 0 } 
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

void Score::SetPosition(const Vector2& position)
{
	m_position = position;
}

void Score::SetWidth(float width)
{
	m_width = width;
}

void Score::SetHeight(float height)
{
	m_height = height;
}

Vector2 Score::GetPosition()
{
	return m_position;
}

float Score::GetWidth()
{
	return m_width;
}

float Score::GetHeight()
{
	return m_height;
}
