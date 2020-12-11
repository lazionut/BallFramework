#include "PickUp.h"

void PickUp::InvokeAction(float time)
{
	m_StopTime = time;
	m_startAction();
}

void PickUp::Move()
{
	m_position += (m_direction * m_speed * Time::GetDeltaTime());
}

void PickUp::ContinueAction()
{
	m_time += Time::GetDeltaTime();

	if (m_time >= m_StopTime)
	{
		m_StopAction();
	}
}

PickUp::PickUp() : m_speed{ 0.0f }, m_time{ 0 }, m_StopTime{ 0 } {}

PickUp::PickUp(std::function<void()> startAction, const Vector2& position, const Vector2& dimension, const Vector2& direction, float speed) :
	m_startAction{ startAction }, m_position{ position }, m_dimension{ dimension }, m_direction{ direction }, 
	m_speed{ speed }, m_time{ 0 }, m_StopTime{ 0 } {}

PickUp::PickUp(std::function<void()> startAction, std::function<void()> stopAction)
	: m_startAction{ startAction }, m_StopAction{ stopAction }, m_time{ 0 }, m_speed{ 0 }, m_StopTime{ 0 } {}

const Vector2& PickUp::GetPosition() const
{
	return m_position;
}

const Vector2& PickUp::GetDimension() const
{
	return m_dimension;
}

const Vector2& PickUp::GetDirection() const
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

void PickUp::SetStartAction(std::function<void()> action)
{
	m_startAction = action;
}

void PickUp::SetStopAction(std::function<void()> action)
{
	m_StopAction = action;
}

void PickUp::SetActions(std::function<void()> startAction, std::function<void()> stopAction)
{
	m_startAction = startAction;
	m_StopAction = stopAction;
}

void PickUp::Set(const Vector2& position, const Vector2& dimension, const Vector2& direction, float speed)
{
	m_position = position;
	m_dimension = dimension;
	m_direction = direction;
	m_speed = speed;
}

void PickUp::SpeedUp()
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


