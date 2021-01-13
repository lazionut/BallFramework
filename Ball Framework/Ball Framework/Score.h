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
		Score(const SDL_Color& color);
		void AddPoints(uint16_t points);

		uint16_t GetScore() const;
		SDL_Color GetScoreColor() const;
		std::string ConvertToString();

		SDL_Texture* GetText() const;
		void SetText(SDL_Texture* text);

		void SetPosition(const Vector2& position);
		void SetWidth(float width);
		void SetHeight(float height);

		const Vector2& GetPosition() const;
		float GetWidth() const;
		float GetHeight() const;

	private:
		uint16_t m_points;
		Vector2 m_position;
		SDL_Texture* m_scoreText;
		SDL_Color m_scoreColor;
		float m_width, m_height;
	};

}