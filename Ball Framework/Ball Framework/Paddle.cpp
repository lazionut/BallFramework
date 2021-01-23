#include "Paddle.h"

namespace BallFramework
{

	Paddle::Paddle() noexcept
		: MovableObject(), m_leftDirection{ Vector2::zero }, m_rightDirection{ Vector2::zero },
		m_leftKey{ NULL }, m_rightKey{ NULL },  m_leftPressed{ false }, m_rightPressed{ false } {}

	Paddle::Paddle(const Vector2& position, const float& width, const float& height, const Vector2& leftDirection, const Vector2& rightDirection, const SDL_Keycode& leftKey,
		const SDL_Keycode& rightKey, float speed) noexcept
		: MovableObject(position, Vector2(width, height), Vector2::zero, speed), 
		m_leftDirection{ leftDirection }, m_rightDirection{ rightDirection },
		m_leftKey{ leftKey }, m_rightKey{ rightKey }, m_leftPressed{ false }, m_rightPressed{ false } 
	{
		m_speed = speed;
		std::cout << "speed" << m_speed;
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
			std::cout << m_direction << "\n";
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

}