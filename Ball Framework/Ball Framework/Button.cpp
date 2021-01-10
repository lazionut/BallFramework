#include "Button.h"

static SDL_Color white = Colors::ReturnBasicColor(static_cast<uint8_t>(Colors::BasicColors::white));
static SDL_Color red = Colors::ReturnBasicColor(static_cast<uint8_t>(Colors::BasicColors::red));;
static SDL_Color black = Colors::ReturnBasicColor(static_cast<uint8_t>(Colors::BasicColors::black));


Button::Button()
	: Rectangle{ Vector2::zero, 0.0f, 0.0f },
	m_text{ "" }, m_backColor{ white },m_fontColor{ black }, m_changedBack{ false }, m_changedFont{ false },
	m_buttonText{ nullptr }, m_rect{ 0, 0, 0, 0 } 
{

}

Button::Button(const Vector2& position, const float& width, const float& height, const SDL_Color& backColor, const SDL_Color& fontColor, const std::string& text)
	: Rectangle{ position, width, height },
	m_text{ text }, m_backColor{ backColor }, m_fontColor{ fontColor }, m_changedBack{ false },
	m_changedFont{ false }, m_buttonText{ nullptr }, m_rect{ 0, 0, 0, 0 }
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

const std::string& Button::GetButtonText() const
{
	return m_text;
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

void Button::ChangeFontColor()
{
	if (!m_changedFont)
	{
		SetFontColor(red);
		m_changedFont = true;
	}
	else
	{
		SetFontColor(white);
		m_changedFont = false;
	}
}

Button::~Button()
{
	SDL_DestroyTexture(m_buttonText);
}

void Button::SetButton(const Vector2& position, const float& width, const float& height, const SDL_Color& backColor, const SDL_Color& fontColor, const std::string& text)
{
	Set(position, width, height);
	m_text = text;
	m_backColor = backColor;
	m_fontColor = fontColor;
}

SDL_Texture* Button::GetText() const
{
	return m_buttonText;
}

void Button::SetText(SDL_Texture* text) 
{
	if (m_buttonText != nullptr) {
		SDL_DestroyTexture(m_buttonText);
		m_buttonText = text;
	}
	else
	{
		m_buttonText = text;
	}
}