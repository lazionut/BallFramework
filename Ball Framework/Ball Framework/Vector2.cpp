#include "Vector2.h"

Vector2::Vector2() :
	m_x{ 0 }, m_y{ 0 } {
}

Vector2::Vector2(float x, float y) :
	m_x{ x }, m_y{ y } {
}

Vector2::Vector2(const Vector2& other)
{
	*this = other;
}

void Vector2::setX(float xCoordinate)
{
	m_x = xCoordinate;
}

float Vector2::getX()
{
	return m_x;
}

void Vector2::setY(float yCoordinate)
{
	m_y = yCoordinate;
}

float Vector2::getY()
{
	return m_y;
}

std::istream& operator>>(std::istream& input, Vector2& other)
{
	input >> other.m_x >> other.m_y;
	return input;
}

std::ostream& operator<<(std::ostream& output, const Vector2& other)
{
	output << "(" << other.m_x << ", " << other.m_y << ")";
	return output;
}