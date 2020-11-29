#include "PickUp.h"

PickUp::PickUp() : m_speed{ 0.0f }
{
}

PickUp::PickUp(std::function<void()> f_action, const Vector2& position, const Vector2& dimension, const Vector2& direction, float speed) :
	m_f_action{ f_action }, m_position{ position }, m_dimension{ dimension }, m_direction{ direction }, m_speed{ speed }
{
}

Vector2 PickUp::GetPosition() const
{
	return m_position;
}

Vector2 PickUp::GetDimension() const
{
	return m_dimension;
}

Vector2 PickUp::GetDirection() const
{
	return m_direction;
}
float PickUp::GetSpeed() const
{
	return m_speed;
}


