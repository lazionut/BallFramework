#pragma once
#include"Vector2.h"

class Ball
{
public:
	Ball();
	Ball(const Vector2& position, float size, const Vector2& direction, float speed);

	Vector2 getPosition();
	float getSize();
	Vector2 getDirection();
	float getSpeed();

	void setPoisiton(const Vector2& position);
	void setPosition(float x, float y);
	void setSize(float size);
	void setDirection(const Vector2& direction);
	void setDirection(float, float y);
	void setSpeed(float speed);


private:
	Vector2 m_position, m_direction;
	float m_size, m_speed;
};
