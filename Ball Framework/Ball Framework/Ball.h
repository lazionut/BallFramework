#pragma once
#include"Vector2.h"
#include"Time.h"

class Ball
{
public:
	Ball();
	Ball(const Vector2& position, float size, const Vector2& direction, float speed);
	Ball(const Ball& other);
	Ball(Ball&& other) noexcept;

	Vector2 Get_Position();
	float Get_Size();
	Vector2 Get_Direction();
	float Get_Speed();

	void Set_Position(const Vector2& position);
	void Set_Position(float x, float y);
	void Set_Size(float size);
	void Set_Direction(const Vector2& direction);
	void Set_Direction(float, float y);
	void Set_Speed(float speed);

	void Move_();

	Ball& operator=(const Ball& other);
	Ball& operator=(Ball&& other)noexcept;

private:
	Vector2 m_position, m_direction;
	float m_size, m_speed;
};