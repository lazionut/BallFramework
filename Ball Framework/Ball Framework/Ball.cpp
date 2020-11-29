#include "Ball.h"

Ball::Ball()
	:m_position{ Vector2::Vector2(0.0f, 0.0f) }, m_size{ 0.0f }, m_direction(), m_speed(0)
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

Vector2 Ball::GetPosition()
{
	return m_position;
}

float Ball::GetSize()
{
	return m_size;
}

Vector2 Ball::GetDirection()
{
	return m_direction;
}

float Ball::GetSpeed()
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