#include "PickUp.h"

void PickUp::InvokeAction()
{
	m_f_action();
}

void PickUp::Move()
{
	m_position += (m_direction * m_speed * Time::GetDeltaTime());
}

PickUp::PickUp() : m_speed{ 0.0f }
{
}

PickUp::PickUp(std::function<void()> f_action, const Vector2& position, const Vector2& dimension, const Vector2& direction, float speed) :
	m_f_action{ f_action }, m_position{ position }, m_dimension{ dimension }, m_direction{ direction }, m_speed{ speed }
{
}

Vector2 PickUp::GetPosition() const
{
	return m_position;
}

Vector2 PickUp::GetDimension() const
{
	return m_dimension;
}

Vector2 PickUp::GetDirection() const
{
	return m_direction;
}
float PickUp::GetSpeed() const
{
	return m_speed;
}

void PickUp::SetPosition(const Vector2& position)
{
	m_position = position;
}

void PickUp::SetDimension(const Vector2& dimension)
{
	m_dimension = dimension;
}

void PickUp::SetDirection(const Vector2& direction)
{
	m_direction = direction;
}

void PickUp::SetSpeed(float speed)
{
	m_speed = speed;
}
void PickUp::Speed()
{
	Time::SetTimeScale(2);
}

void PickUp::SlowDown()
{
	Time::SetTimeScale(1);
}

void PickUp::SmallerPaddle(Paddle& paddle)
{
	paddle.SetWidth(paddle.GetWidth() - 2);
}

void PickUp::BiggerPaddle(Paddle& paddle)
{
	paddle.SetWidth(paddle.GetWidth() + 2);
}

void PickUp::BiggerBall(Ball& ball, float x)
{
	ball.SetSize(ball.GetSize() + 1);
}

void PickUp::SmallerBall(Ball& ball, float x)
{
	ball.SetSize(ball.GetSize() - 1);
}


