#include "Ball.h"

Ball::Ball()
	: m_position{ Vector2::Vector2(0.0f, 0.0f) }, m_size{ 0.0f }, m_direction(), m_speed(0)
{
}

Ball::Ball(const Vector2& position, float size, const Vector2& direction, float speed)
	: m_position(position), m_size(size), m_direction(direction), m_speed(speed)
{
}

Ball::Ball(const Ball& other)
{
	*this = other;
}

const Vector2& Ball::GetPosition() const
{
	return m_position;
}

float Ball::GetSize() const
{
	return m_size;
}

const Vector2& Ball::GetDirection() const
{
	return m_direction;
}

Vector2& Ball::GetDirection()
{
	return m_direction;
}

float Ball::GetSpeed() const
{
	return m_speed;
}

void Ball::SetPosition(const Vector2& position)
{
	m_position = position;
}

void Ball::SetPosition(float x, float y)
{
	m_position.Set(x, y);
}

void Ball::SetSize(float size)
{
	m_size = size;
}

void Ball::SetDirection(const Vector2& direction)
{
	m_direction = direction;
}

void Ball::SetDirection(float x, float y)
{
	m_direction.Set(x, y);
}

void Ball::SetSpeed(float speed)
{
	m_speed = speed;
}

void Ball::AddSpeed(float difference)
{
	m_speed += difference;
}

void Ball::Move()
{
	m_position += (m_direction * m_speed * Time::GetDeltaTime());
}

bool Ball::CheckCollision(const Rectangle& rect)
{
	float x, y;
	float ballx = m_position.GetX(), bally = m_position.GetY();
	float rectWidth = rect.GetWidth();
	float rectHeight = rect.GetHeight();
	float rectx = rect.GetPosition().GetX() - rectWidth / 2;
	float recty = rect.GetPosition().GetY() - rectHeight / 2;
	
	if (ballx < rectx)
	{
		x = rectx;
	}
	else if (ballx > rectx + rectWidth)
	{
		x = rectx + rectWidth;
	}
	else
	{
		x = ballx;
	}

	if (bally < recty)
	{
		y = recty;
	}
	else if (bally > recty + rectHeight)
	{
		y = recty + rectHeight;
	}
	else
	{
		y = bally;
	}

	float delta1 = x - ballx;
	float delta2 = y - bally;

	//float difference = (m_size * m_size / 4) - (delta1 * delta1 + delta2 * delta2);

	if (delta1 * delta1 + delta2 * delta2 < (m_size * m_size / 4))
	{
		Vector2 difference{ delta1, delta2 };
		difference.Normalize();
		difference *= m_size / 2;

		m_position = Vector2(x, y) - difference;

		return true;
	}


	return false;
}

void Ball::ChangeDirection(const Rectangle& rect)
{
	auto xRect = rect.GetPosition().GetX();
	auto yRect = rect.GetPosition().GetY();
	

	if (m_position.GetY() <= yRect + (rect.GetHeight() / 2) && m_position.GetY() >= yRect - rect.GetHeight() / 2)
	{
		
		if (m_position.GetX() < xRect && m_direction.GetX() < 0)
		
			m_position.SetX(m_position.GetX() - m_size);
		
		else
		{
			if (m_position.GetX() > xRect && m_direction.GetX() > 0)

			m_position.SetX(m_position.GetX() + m_size);

			else
				m_direction.SetX(m_direction.GetX() * (-1));
		}
	}

	else
	{
		if (m_position.GetX() <= xRect + (rect.GetWidth() / 2) && m_position.GetX() >= xRect - (rect.GetWidth() / 2))
		{
			
			if (m_position.GetY() < yRect && m_direction.GetY() < 0)

				m_position.SetY(m_position.GetY() - m_size);
			else
			{
				if (m_position.GetY() > yRect && m_direction.GetY() > 0)

					m_position.SetY(m_position.GetY() + m_size);
				else 
					m_direction.SetY(m_direction.GetY() * (-1));
			}
			
		}
		else {
			
				if (m_position.GetY() > yRect)
				{
					if (m_position.GetX() >= xRect)
						m_direction.Set(1, 1);
					else
						m_direction.Set(-1, 1);
				}
				else
				{
					if (m_position.GetX() > xRect)
						m_direction.Set(1, -1);
					else
						m_direction.Set(-1, -1);
				}
			
		}
	}
}

Ball& Ball::operator=(const Ball& other)
{
	m_position = other.m_position;
	m_size = other.m_size;
	m_direction = other.m_direction;
	m_speed = other.m_speed;
	return *this;
}

Ball& Ball::operator=(Ball&& other) noexcept
{
	m_position = other.m_position;
	m_size = other.m_size;
	m_direction = other.m_direction;
	m_speed = other.m_speed;
	new(&other)Ball;
	return *this;
}