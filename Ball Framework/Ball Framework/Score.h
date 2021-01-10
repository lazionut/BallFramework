#pragma once
#include <cstdint>
#include <string>
#include <SDL_ttf.h>
#include <iostream>
#include "Vector2.h"

namespace BallFramework
{

	class Score
	{
	public:
		Score(TTF_Font* font);
		void AddPoints(uint16_t points);
		uint16_t GetScore() const;
		std::string ConvertToString();

		SDL_Texture* GetText(SDL_Renderer* renderer);

		void SetPosition(const Vector2& position);
		void SetWidth(float width);
		void SetHeight(float height);

		Vector2 GetPosition();
		float GetWidth();
		float GetHeight();

	private:
		uint16_t m_points;
		TTF_Font* m_font;
		Vector2 m_position;
		float m_width, m_height;
	};

}