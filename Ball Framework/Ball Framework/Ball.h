#pragma once
#include"Vector2.h"

class Ball
{
public:
	Ball();
	Ball(const Vector2& position, float size, const Vector2& direction, float speed);

private:
	Vector2 m_position, m_direction;
	float m_size, m_speed;
};
