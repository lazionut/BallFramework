#pragma once

#include <cstdint>
#include <string>
#include <SDL_ttf.h>
#include <iostream>
#include "GameObject.h"

namespace BallFramework
{

	class Score : public GameObject
	{
	public:
		Score(const SDL_Color& color);
		void AddPoints(int16_t points);

		int16_t GetScore() const;
		SDL_Color GetScoreColor() const;
		std::string ConvertToString();

		SDL_Texture* GetText() const;
		void SetText(SDL_Texture* text);

		void SetScore(int16_t points);

	private:
		int16_t m_points;
		SDL_Texture* m_scoreText;
		SDL_Color m_scoreColor;
	};

}