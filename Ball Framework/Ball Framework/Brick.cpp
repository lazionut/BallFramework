#include "Brick.h"

BallFramework::Brick::Brick()
	: Rectangle(), m_id{ 0 }, m_color{ 0, 0, 0, 0 } {}

BallFramework::Brick::Brick(const Vector2& position, const float width, const float height)
	: Rectangle(position, width, height), m_id{ 0 }, m_color{ 0, 0, 0, 0 } {}

BallFramework::Brick::Brick(const Vector2& position, const float width, const float height, uint16_t m_id, SDL_Color color)
	: Rectangle(position, width, height), m_id{ 0 }, m_color{ color } {}

BallFramework::Brick::Brick(const Brick& other) 
	: Rectangle(other) , m_id{other.m_id}, m_color{other.m_color} {}

uint16_t BallFramework::Brick::GetId() const noexcept
{
	return m_id;
}

SDL_Color BallFramework::Brick::GetColor() const noexcept
{
	return m_color;
}

void BallFramework::Brick::SetId(uint16_t id) noexcept
{
	m_id = id;
}

void BallFramework::Brick::SetColor(SDL_Color color) noexcept
{
	m_color = color;
}
