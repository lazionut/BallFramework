#include "Paddle.h"
Paddle::Paddle()
	: m_direction{ Vector2::zero }, m_leftDirection{ Vector2::zero }, m_rightDirection{ Vector2::zero },
	m_leftKey{ NULL }, m_rightKey{ NULL }, m_leftLimit{ Vector2::zero },
	m_rightLimit{ Vector2::zero }, m_speed{ 0 }
{
}

Paddle::Paddle(const Vector2& leftDirection, const Vector2& rightDirection, const SDL_Keycode& leftKey,
	const SDL_Keycode& rightKey, const  Vector2& leftLimit, const  Vector2& rightLimit, float speed)

	: m_direction{ Vector2::zero }, m_leftDirection{ leftDirection }, m_rightDirection{ rightDirection },
	m_leftKey{ leftKey }, m_rightKey{ rightKey }, m_leftLimit{ leftLimit },
	m_rightLimit{ rightLimit }, m_speed{ speed }
{
}

void Paddle::Move()
{
	m_position += (m_direction * m_speed * Time::GetDeltaTime());
}

void Paddle::CheckBounds()
{
	if (m_position > m_leftLimit)
	{
		m_position = m_leftLimit;
	}
	else if (m_position > m_rightLimit)
	{
		m_position = m_rightLimit;
	}
}

void Paddle::KeyPressed(const SDL_Keycode& key)
{
	if (key == m_leftKey)
	{
		m_direction = m_leftDirection;
	}
	else if (key == m_rightKey)
	{
		m_direction = m_rightDirection;
	}
}

void Paddle::KeyReleased(const SDL_Keycode& key)
{
	if (key == m_leftKey || key == m_rightKey)
	{
		m_direction = Vector2::zero;
	}
}

float Paddle::GetSpeed() const
{
	return m_speed;
}

void Paddle::SetSpeed(float speed)
{
	m_speed = speed;
}