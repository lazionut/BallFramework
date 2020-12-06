#include "Score.h"

Score::Score()
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
	TTF_Font* font = TTF_OpenFont("Adoring.ttf", 24);
	if (font == NULL) {
		std::cout << "Could not load the text! " << TTF_GetError()<<std::endl;
		TTF_CloseFont(font);
		return nullptr;
	}
	SDL_Color white = { 255, 255, 255 };
	SDL_Surface* loadedText = TTF_RenderText_Solid(font, ConvertToString().c_str(), white);

	if (loadedText)
	{
		SDL_Texture* result = SDL_CreateTextureFromSurface(renderer, loadedText);
		SDL_FreeSurface(loadedText);
		TTF_CloseFont(font);
		return result;
	}

	std::cout << "Could not load the text!\n";
	TTF_CloseFont(font);
	return nullptr;
}