#pragma once
#include <iostream>

class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& other);

	void SetX(float xCoordinate);
	float GetX() const;
	float& GetX();
	void SetY(float yCoordinate);
	float GetY() const;
	float& GetY();
	void Set(float xCoordinate, float yCoordinate);

	float GetLength() const;
	float GetSquareLength() const;
	void Normalize();
	Vector2 GetNormalized();

	Vector2 operator+(const Vector2& other) const;
	Vector2& operator+=(const Vector2& other);
	Vector2 operator-(const Vector2& other) const;
	Vector2& operator-=(const Vector2& other);
	Vector2 operator*(float scalar) const;
	Vector2& operator*=(float scalar);
	Vector2 operator/(float scalar) const;
	Vector2& operator/=(float scalar);
	Vector2& operator=(const Vector2& other);
	bool operator<(const Vector2& other) const;
	bool operator<=(const Vector2& other) const;
	bool operator>(const Vector2& other) const;
	bool operator>=(const Vector2& other) const;
	bool operator==(const Vector2& other) const;
	bool operator!=(const Vector2& other) const;

	const static Vector2 zero;
	const static Vector2 one;
	const static Vector2 up;
	const static Vector2 down;
	const static Vector2 left;
	const static Vector2 right;

	friend std::istream& operator>>(std::istream& input, Vector2& other);
	friend std::ostream& operator<<(std::ostream& output, const Vector2& other);

private:
	float m_x;
	float m_y;
};