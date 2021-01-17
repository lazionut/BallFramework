#include "Score.h"

namespace BallFramework
{

	Score::Score(const SDL_Color& color) :
		m_scoreColor{ color },
		m_position{ Vector2::zero },
		m_width{ 0 }, m_height{ 0 },
		m_scoreText{ nullptr }
	{
		m_points = 0;
	}

	void Score::AddPoints(int16_t points)
	{
		m_points += points;
	}

	int16_t Score::GetScore() const
	{
		return m_points;
	}

	SDL_Color Score::GetScoreColor() const
	{
		return m_scoreColor;
	}

	std::string Score::ConvertToString()
	{
		return std::to_string(m_points);
	}

	SDL_Texture* Score::GetText() const
	{
		return m_scoreText;
	}

	void Score::SetText(SDL_Texture* text)
	{
		if (m_scoreText != nullptr) {
			SDL_DestroyTexture(m_scoreText);
			m_scoreText = text;
		}
		else
		{
			m_scoreText = text;
		}
	}

	void Score::SetScore(int16_t points)
	{
		m_points = points;
	}

	void Score::SetPosition(const Vector2& position)
	{
		m_position = position;
	}

	void Score::SetWidth(float width)
	{
		m_width = width;
	}

	void Score::SetHeight(float height)
	{
		m_height = height;
	}

	const Vector2& Score::GetPosition() const
	{
		return m_position;
	}

	float Score::GetWidth() const
	{
		return m_width;
	}

	float Score::GetHeight() const
	{
		return m_height;
	}

}