#pragma once
#include <functional>
#include "Vector2.h"
#include "Time.h"
class PickUp
{
public:
	PickUp();
	PickUp(std::function<void()> f_action, const Vector2& position, const Vector2& dimension, const Vector2& direction, float speed);

	Vector2 GetPosition() const;
	Vector2 GetDimension() const;
	Vector2 GetDirection() const;
	float GetSpeed() const;

private:
	std::function<void()> m_f_action;
	Vector2 m_position, m_dimension, m_direction;
	float m_speed;

};

