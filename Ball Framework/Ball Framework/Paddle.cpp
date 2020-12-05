#include "Paddle.h"
Paddle::Paddle()
	: m_direction{ Vector2::zero }, m_leftDirection{ Vector2::zero }, m_rightDirection{ Vector2::zero },
	m_leftKey{ NULL }, m_rightKey{ NULL }, m_speed{ 0 }, m_leftPressed{ false }, m_rightPressed{ false }
{
}

Paddle::Paddle(const Vector2& position, const float& width, const float& height, const Vector2& leftDirection, const Vector2& rightDirection, const SDL_Keycode& leftKey,
	const SDL_Keycode& rightKey, float speed)

	:Rectangle{position, width, height},
	m_direction{ Vector2::zero }, m_leftDirection{ leftDirection }, m_rightDirection{ rightDirection },
	m_leftKey{ leftKey }, m_rightKey{ rightKey }, m_speed{ speed }, m_leftPressed{ false}, m_rightPressed{ false }
{
}

void Paddle::Move()
{
	m_position += (m_direction * m_speed * Time::GetDeltaTime());
}

void Paddle::KeyPressed(const SDL_Keycode& key)
{
	if (key == m_leftKey && !m_leftPressed)
	{
		m_leftPressed = true;
		m_direction += m_leftDirection;
	}
	else if (key == m_rightKey && !m_rightPressed)
	{
		m_rightPressed = true;
		m_direction += m_rightDirection;
	}
}

void Paddle::KeyReleased(const SDL_Keycode& key)
{
	if (key == m_leftKey)
	{
		m_leftPressed = false;
		m_direction -= m_leftDirection;
	}
	else if (key == m_rightKey)
	{
		m_rightPressed = false;
		m_direction -= m_rightDirection;
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