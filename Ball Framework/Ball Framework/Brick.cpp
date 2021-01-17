#include "Brick.h"

namespace BallFramework
{

	Brick::Brick()
		: Rectangle(), m_id{ 0 }, m_color{ 0, 0, 0, 0 } {}

	Brick::Brick(const Vector2& position, const float width, const float height)
		: Rectangle(position, width, height), m_id{ 0 }, m_color{ 0, 0, 0, 0 } {}

	Brick::Brick(const Vector2& position, const float width, const float height, uint16_t m_id, SDL_Color color)
		: Rectangle(position, width, height), m_id{ 0 }, m_color{ color } {}

	Brick::Brick(const Brick& other)
		: Rectangle(other), m_id{ other.m_id }, m_color{ other.m_color } {}

	uint16_t Brick::GetId() const noexcept
	{
		return m_id;
	}

	SDL_Color Brick::GetColor() const noexcept
	{
		return m_color;
	}

	void Brick::SetId(uint16_t id) noexcept
	{
		m_id = id;
	}

	void Brick::SetColor(SDL_Color color) noexcept
	{
		m_color = color;
	}

}