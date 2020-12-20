#pragma once
#include "Rectangle.h"
#include <SDL_ttf.h>


class Button : public Rectangle
{
public:
	Button();
	Button(const Vector2& position, const float& width, const float& height, const SDL_Color& backColor, const SDL_Color& fontColor, const std::string& name);

	SDL_Color GetBackColor() const;
	SDL_Color GetFontColor() const;
	void SetButton(const Vector2& position, const float& width, const float& height, const SDL_Color& bcakColor, const SDL_Color& fontColor, const std::string& name);
	SDL_Texture* GetText(SDL_Renderer* renderer, TTF_Font* font);
	SDL_Rect GetRect() const;
	void SetRect(const SDL_Rect& rect);
	void SetBackColor(const SDL_Color& color);
	void SetFontColor(const SDL_Color& color);
	void ChangeBackColor();

	void ChangeFontColor();

private:
	std::string m_name;
	SDL_Color m_backColor;
	SDL_Color m_fontColor;
	SDL_Rect m_rect;
	bool m_changedBack;
	bool m_changedFont;
};