#pragma once
#include "Rectangle.h"
#include "Colors.h"
#include <SDL_ttf.h>

namespace BallFramework
{

	class Button : public Rectangle
	{
	public:
		Button();
		Button(const Vector2& position, const float& width, const float& height, const SDL_Color& backColor, const SDL_Color& fontColor, const std::string& text);

		SDL_Color GetBackColor() const;
		SDL_Color GetFontColor() const;

		void SetButton(const Vector2& position, const float& width, const float& height, const SDL_Color& backColor, const SDL_Color& fontColor, const std::string& text);

		SDL_Texture* GetText() const;
		SDL_Rect GetRect() const;
		const std::string& GetButtonText() const;

		void SetRect(const SDL_Rect& rect);
		void SetText(SDL_Texture* text);
		void SetBackColor(const SDL_Color& color);
		void SetFontColor(const SDL_Color& color);

		void ChangeBackColor();
		void ChangeFontColor();

		~Button();

	private:
		std::string m_text;
		SDL_Color m_backColor;
		SDL_Color m_fontColor;
		SDL_Rect m_rect;
		SDL_Texture* m_buttonText;

		bool m_changedBack;
		bool m_changedFont;
	};

}