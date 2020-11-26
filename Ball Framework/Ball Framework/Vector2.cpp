#include "Vector2.h"
#include <cmath>

Vector2::Vector2() :
	m_x{ 0.0f }, m_y{ 0.0f } {
}

Vector2::Vector2(float x, float y) :
	m_x{ x }, m_y{ y } {
}

Vector2::Vector2(const Vector2& other)
{
	*this = other;
}

void Vector2::SetX(float xCoordinate)
{
	m_x = xCoordinate;
}

float Vector2::GetX()
{
	return m_x;
}

void Vector2::SetY(float yCoordinate)
{
	m_y = yCoordinate;
}

float Vector2::GetY()
{
	return m_y;
}

void Vector2::Set(float xCoordinate, float yCoordinate)
{
	m_x = xCoordinate;
	m_y = yCoordinate;
}

float Vector2::GetLength() const
{
	return sqrt(m_x * m_x + m_y * m_y);
}

float Vector2::GetSquareLength() const
{
	return m_x * m_x + m_y * m_y;
}

void Vector2::Normalize()
{
	float length = GetLength();
	m_x /= length;
	m_y /= length;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(this->m_x + other.m_x, this->m_y + other.m_y);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	m_x += other.m_x;
	m_y += other.m_y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(this->m_x - other.m_x, this->m_y - other.m_y);
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	m_x -= other.m_x;
	m_y -= other.m_y;
	return *this;
}

Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(m_x * scalar, m_y * scalar);
}

Vector2& Vector2::operator*=(float scalar)
{
	m_x = m_x * scalar;
	m_y = m_y * scalar;
	return *this;
}

Vector2 Vector2::operator/(float scalar) const
{
	return Vector2(m_x / scalar, m_y / scalar);
}

Vector2& Vector2::operator/=(float scalar)
{
	m_x = m_x / scalar;
	m_y = m_y / scalar;
	return *this;
}

Vector2& Vector2::operator=(const Vector2& other)
{
	m_x = other.m_x;
	m_y = other.m_y;
	return *this;
}

bool Vector2::operator<(const Vector2& other) const
{
	return GetSquareLength() < other.GetSquareLength();
}

bool Vector2::operator<=(const Vector2& other) const
{
	return GetSquareLength() <= other.GetSquareLength();
}

bool Vector2::operator>(const Vector2& other) const
{
	return GetSquareLength() > other.GetSquareLength();
}

bool Vector2::operator>=(const Vector2& other) const
{
	return GetSquareLength() >= other.GetSquareLength();
}

bool Vector2::operator==(const Vector2& other) const
{
	return m_x == other.m_x && m_y == other.m_y;
}

bool Vector2::operator!=(const Vector2& other) const
{
	return GetSquareLength() != other.GetSquareLength();
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