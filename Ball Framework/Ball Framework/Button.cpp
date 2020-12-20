#include "Button.h"

static SDL_Color white = { 255, 255, 255, 255 };
static SDL_Color red = { 255, 0, 0, 255 };
static SDL_Color black = { 0, 0, 0, 0 };


Button::Button()
	: Rectangle{ Vector2::zero, 0.0f, 0.0f },
	m_name{ "" }, m_backColor{ white }, m_fontColor{ black }, m_changedBack{ false }, m_changedFont{ false }
{
}
Button::Button(const Vector2& position, const float& width, const float& height, const SDL_Color& backColor, const SDL_Color& fontColor, const std::string& name)
	: Rectangle{ position, width, height },
	m_name{ name }, m_backColor{ backColor }, m_fontColor{ fontColor }, m_changedBack{ false }, m_changedFont{ false }
{
}

SDL_Color Button::GetBackColor() const
{
	return m_backColor;
}

SDL_Color Button::GetFontColor() const
{
	return m_backColor;
}

void Button::SetRect(const SDL_Rect& rect) {
	m_rect = rect;
}

void Button::SetBackColor(const SDL_Color& color)
{
	m_backColor = color;
}

void Button::SetFontColor(const SDL_Color& color)
{
	m_fontColor = color;
}

SDL_Rect Button::GetRect() const {
	return m_rect;
}

void Button::ChangeBackColor()
{
	if (!m_changedBack) {
		SetBackColor(red);
		m_changedBack = true;
	}
	else {
		SetBackColor(white);
		m_changedBack = false;
	}
}

void Button::ChangeFontColor()
{
	if (!m_changedFont) {
		SetFontColor(red);
		m_changedFont = true;
	}
	else {
		SetFontColor(white);
		m_changedFont = false;
	}
}

void Button::SetButton(const Vector2& position, const float& width, const float& height, const SDL_Color& backColor, const SDL_Color& fontColor, const std::string& name)
{
	Set(position, width, height);
	m_name = name;
	m_backColor = backColor;
	m_fontColor = fontColor;

}

SDL_Texture* Button::GetText(SDL_Renderer* renderer, TTF_Font* font)
{
	SDL_Surface* loadedText = TTF_RenderText_Solid(font, m_name.c_str(), m_fontColor);
	if (loadedText)
	{
		SDL_Texture* result = SDL_CreateTextureFromSurface(renderer, loadedText);
		SDL_FreeSurface(loadedText);
		return result;
	}
}