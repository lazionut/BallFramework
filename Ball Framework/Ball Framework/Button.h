#pragma once
#include "Rectangle.h"
#include <SDL_ttf.h>


class Button : public Rectangle
{
public:
	Button();
	Button(const Vector2& position, const float& width, const float& height, const std::string& name);

	SDL_Color GetColor() const;
	void SetButton(const Vector2& position, const float& width, const float& height, const std::string& name);
	SDL_Texture* GetText(SDL_Renderer* renderer, TTF_Font* font);
	SDL_Rect GetRect() const;
	void SetRect(const SDL_Rect& rect);
	void SetBackColor(const SDL_Color& color);
	void ChangeBackColor();

private:
	std::string m_name;
	SDL_Color m_backColor;
	SDL_Rect m_rect;
	bool m_changed;
};