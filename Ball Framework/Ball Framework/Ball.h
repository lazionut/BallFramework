#pragma once
#include"Vector2.h"
#include"Time.h"
#include "Rectangle.h"

class Ball
{
public:
	Ball();
	Ball(const Vector2& position, float size, const Vector2& direction, float speed);
	Ball(const Ball& other);

	Vector2 GetPosition() const;
	float GetSize() const;
	Vector2 GetDirection() const;
	float GetSpeed() const;

	void SetPosition(const Vector2& position);
	void SetPosition(float x, float y);
	void SetSize(float size);
	void SetDirection(const Vector2& direction);
	void SetDirection(float x, float y);
	void SetSpeed(float speed);

	void Move();
	bool CheckCollision(const Rectangle& rect);
	void ChangeDirection(const Rectangle& rect);

	Ball& operator=(const Ball& other);
	Ball& operator=(Ball&& other)noexcept;

private:
	Vector2 m_position, m_direction;
	float m_size, m_speed;
};