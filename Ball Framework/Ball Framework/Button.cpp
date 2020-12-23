#include "Button.h"

static SDL_Color white = { 255, 255, 255, 255 };
static SDL_Color red = { 255, 0, 0, 255 };
static SDL_Color black = { 0, 0, 0, 255 };


Button::Button()
	: Rectangle{ Vector2::zero, 0.0f, 0.0f },
	m_text{ "" }, m_backColor{ white },m_fontColor{ black }, m_changedBack{ false }, m_changedFont{ false },
	m_buttonText{ nullptr }, m_loadedText{ nullptr }, m_font{ nullptr }, m_rect{ 0, 0, 0, 0 } 
{

}

Button::Button(const Vector2& position, const float& width, const float& height, const SDL_Color& backColor, const SDL_Color& fontColor, const std::string& text, TTF_Font* font)
	: Rectangle{ position, width, height },
	m_text{ text }, m_backColor{ backColor }, m_fontColor{ fontColor }, m_changedBack{ false },
	m_changedFont{ false }, m_buttonText{ nullptr }, m_loadedText{ nullptr }, m_font{ font }, m_rect{ 0, 0, 0, 0 }
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

void Button::SetRect(const SDL_Rect& rect) 
{
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

SDL_Rect Button::GetRect() const 
{
	return m_rect;
}

void Button::ChangeBackColor()
{
	if (!m_changedBack)
	{
		SetBackColor(red);
		m_changedBack = true;
	}
	else
	{
		SetBackColor(white);
		m_changedBack = false;
	}
}

void Button::ChangeFontColor(SDL_Renderer* renderer)
{
	if (!m_changedFont)
	{
		SetFontColor(red);
		UpdateTextures(renderer);
		m_changedFont = true;
	}
	else
	{
		SetFontColor(white);
		UpdateTextures(renderer);
		m_changedFont = false;
	}
}

void Button::UpdateTextures(SDL_Renderer* renderer)
{
	SDL_DestroyTexture(m_buttonText);

	m_loadedText = TTF_RenderText_Solid(m_font, m_text.c_str(), m_fontColor);
	m_buttonText = SDL_CreateTextureFromSurface(renderer, m_loadedText);
	SDL_FreeSurface(m_loadedText);
}

Button::~Button()
{
	SDL_DestroyTexture(m_buttonText);
}

void Button::SetButton(const Vector2& position, const float& width, const float& height, const SDL_Color& backColor, const SDL_Color& fontColor, const std::string& text, TTF_Font* font)
{
	Set(position, width, height);
	m_text = text;
	m_backColor = backColor;
	m_fontColor = fontColor;
	m_font = font;
}

SDL_Texture* Button::GetText(SDL_Renderer* renderer)
{
	if (m_buttonText == nullptr)
	{
		UpdateTextures(renderer);
	}
	return m_buttonText;
}