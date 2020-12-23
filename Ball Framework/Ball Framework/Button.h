#pragma once
#include "Rectangle.h"
#include <SDL_ttf.h>


class Button : public Rectangle
{
public:
	Button();
	Button(const Vector2& position, const float& width, const float& height, const SDL_Color& backColor, const SDL_Color& fontColor, const std::string& text, TTF_Font* font);

	SDL_Color GetBackColor() const;
	SDL_Color GetFontColor() const;

	void SetButton(const Vector2& position, const float& width, const float& height, const SDL_Color& backColor, const SDL_Color& fontColor, const std::string& text, TTF_Font* font);
	SDL_Texture* GetText(SDL_Renderer* renderer);

	SDL_Rect GetRect() const;
	void SetRect(const SDL_Rect& rect);

	void SetBackColor(const SDL_Color& color);
	void SetFontColor(const SDL_Color& color);
	void ChangeBackColor();
	void ChangeFontColor(SDL_Renderer* renderer);

	void UpdateTextures(SDL_Renderer* renderer);

private:
	std::string m_text;
	SDL_Color m_backColor;
	SDL_Color m_fontColor;
	SDL_Rect m_rect;
	TTF_Font* m_font;
	SDL_Texture* m_buttonText;
	SDL_Surface* m_loadedText;
	bool m_changedBack;
	bool m_changedFont;
};