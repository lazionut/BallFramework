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


Ball::Ball(Ball&& other) noexcept
{
	*this = std::move(other);
}

Vector2 Ball::Get_Position()
{
	return m_position;
}

float Ball::Get_Size()
{
	return m_size;
}

Vector2 Ball::Get_Direction()
{
	return m_direction;
}

float Ball::Get_Speed()
{
	return m_speed;
}

void Ball::Set_Position(const Vector2& position)
{
	m_position = position;
}

void Ball::Set_Position(float x, float y)
{
	m_position.Set_X(x);
	m_position.Set_Y(y);
}

void Ball::Set_Size(float size)
{
	m_size = size;
}

void Ball::Set_Direction(const Vector2& direction)
{
	m_direction = direction;
}

void Ball::Set_Direction(float x, float y)
{
	m_direction.Set_X(x);
	m_direction.Set_Y(y);
}

void Ball::Set_Speed(float speed)
{
	m_speed = speed;
}

void Ball::Move_()
{
	m_position += (m_direction * m_speed * Time::Get_Delta_Time());
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