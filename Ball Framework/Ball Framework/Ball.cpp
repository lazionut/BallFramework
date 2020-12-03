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

Vector2 Ball::GetPosition() const
{
	return m_position;
}

float Ball::GetSize() const
{
	return m_size;
}

Vector2 Ball::GetDirection() const
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
	m_direction.SetX(x);
	m_direction.SetY(y);
}

void Ball::SetSpeed(float speed)
{
	m_speed = speed;
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
		x = rectx + rectHeight;
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

	if (delta1 * delta1 + delta2 * delta2 < (m_size * m_size / 4))
	{
		return true;
	}


	return false;
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