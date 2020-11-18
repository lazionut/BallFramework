#pragma once
#include <iostream>

class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& other);

	void setX(float xCoordinate);
	float getX();
	void setY(float yCoordinate);
	float getY();

	friend std::istream& operator>>(std::istream& input, Vector2& other);
	friend std::ostream& operator<<(std::ostream& output, const Vector2& other);

private:
	float m_x;
	float m_y;
};