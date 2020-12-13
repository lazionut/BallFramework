#include "Button.h"

static SDL_Color white = { 255, 255, 255, 255 };
static SDL_Color red = { 255, 0, 0, 255 };
static SDL_Color black = { 0, 0, 0, 0 };


Button::Button()
	: Rectangle{ Vector2::zero, 0.0f, 0.0f },
	m_name{ "" }, m_backColor{ white }
{
}
Button::Button(const Vector2& position, const float& width, const float& height, const std::string& name)
	: Rectangle{ position, width, height },
	m_name{ name }, m_backColor{ white }
{
}

const SDL_Color& Button::GetColor()
{
	return m_backColor;
}

void Button::SetRect(const SDL_Rect& rect) {
	m_rect = rect;
}

SDL_Rect Button::GetRect() const {
	return m_rect;
}

void Button::SetButton(const Vector2& position, const float& width, const float& height, const std::string& name)
{
	Set(position, width, height);
	m_name = name;
}

SDL_Texture* Button::GetText(SDL_Renderer* renderer, TTF_Font* font)
{
	SDL_Surface* loadedText = TTF_RenderText_Solid(font, m_name.c_str(), black);
	if (loadedText)
	{
		SDL_Texture* result = SDL_CreateTextureFromSurface(renderer, loadedText);
		SDL_FreeSurface(loadedText);
		return result;
	}
}