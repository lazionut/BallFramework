#pragma once
#include"Vector2.h"
#include"Time.h"

class Ball
{
public:
	Ball();
	Ball(const Vector2& position, float size, const Vector2& direction, float speed);
	Ball(const Ball& other);
	Ball(Ball&& other)noexcept;

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

	void move();

	Ball& operator=(const Ball& other);
	Ball& operator=(Ball&& other)noexcept;

private:
	Vector2 m_position, m_direction;
	float m_size, m_speed;
};
