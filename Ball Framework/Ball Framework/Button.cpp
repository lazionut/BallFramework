#include "Button.h"

static SDL_Color white = { 255, 255, 255, 255 };
static SDL_Color red = { 255, 0, 0, 255 };
static SDL_Color black = { 0, 0, 0, 0 };


Button::Button()
	: Rectangle{ Vector2::zero, 0.0f, 0.0f },
	m_text{ "" }, m_backColor{ white }, m_fontColor{ black }, m_changedBack{ false }, m_changedFont{ false }, m_buttonTexture{ nullptr }, m_loadedText{ nullptr }
{
}
Button::Button(const Vector2& position, const float& width, const float& height, const SDL_Color& backColor, const SDL_Color& fontColor, const std::string& text)
	: Rectangle{ position, width, height },
	m_text{ text }, m_backColor{ backColor }, m_fontColor{ fontColor }, m_changedBack{ false }, m_changedFont{ false }, m_buttonTexture{nullptr}, m_loadedText{nullptr}
{
}

SDL_Color Button::GetBackColor() const
{
	return m_backColor;
}

SDL_Color Button::GetFontColor() const
{
	return m_fontColor;
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
	m_text = name;
	m_backColor = backColor;
	m_fontColor = fontColor;

}

SDL_Texture* Button::GetText(SDL_Renderer* renderer, TTF_Font* font)
{
	if (!m_buttonTexture) 
	{
		if (!m_loadedText) {
			m_loadedText = TTF_RenderText_Solid(font, m_text.c_str(), m_fontColor);
			if (m_loadedText)
			{
				m_buttonTexture = SDL_CreateTextureFromSurface(renderer, m_loadedText);
			}
		}
	}
	return m_buttonTexture;
}