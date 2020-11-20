#include "Ball.h"

Ball::Ball()
	:m_position{ Vector2::Vector2(0.0f, 0.0f) }, m_size{ 0.0f }, m_direction(), m_speed(0)
{
}

Ball::Ball(const Vector2& position, float size, const Vector2& direction, float speed)
	: m_position(position), m_size(size), m_direction(direction), m_speed(speed)
{
}

Vector2 Ball::getPosition()
{
	return m_position;
}

float Ball::getSize()
{
	return m_size;
}

Vector2 Ball::getDirection()
{
	return m_direction;
}

float Ball::getSpeed()
{
	return m_speed;
}

void Ball::setPoisiton(const Vector2& position)
{
	m_position = position;
}

void Ball::setPosition(float x, float y)
{
	m_position.setX(x);
	m_position.setY(y);
}

void Ball::setSize(float size)
{
	m_size = size;
}

void Ball::setDirection(const Vector2& direction)
{
	m_direction = direction;
}

void Ball::setDirection(float x, float y)
{
	m_direction.setX(x);
	m_direction.setY(y);
}

void Ball::setSpeed(float speed)
{
	m_speed = speed;
}