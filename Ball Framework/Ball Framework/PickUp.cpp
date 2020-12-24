#include "PickUp.h"

void PickUp::InvokeAction(float time)
{
	m_StopTime = time;
	m_isMoving = false;
	m_isActionActive = true;

	if (m_startAction)
	{
		m_startAction();
	}
}

void PickUp::ContinueAction()
{
	m_time += Time::GetUnscaledDeltaTime();

	if (m_time >= m_StopTime)
	{
		if (m_StopAction)
		{
			m_StopAction();
			m_isActionActive = false;
		}
	}
}

void PickUp::StartMoving()
{
	m_isMoving = true;
}

PickUp::PickUp() : m_time{ 0 }, m_StopTime{ 0 }, m_isActionActive{ false }, m_isMoving{ false } {}

PickUp::PickUp(std::function<void()> startAction, const Vector2& position, const float size, const Vector2& direction, float speed) 
	: Ball(position, size, direction, speed),
	m_startAction{ startAction }, m_time{ 0 }, m_StopTime{ 0 }, m_isActionActive{ false }, m_isMoving{ false } {}

PickUp::PickUp(std::function<void()> startAction, std::function<void()> stopAction)
	: m_startAction{ startAction }, m_StopAction{ stopAction }, m_time{ 0 }, 
	m_StopTime{ 0 }, m_isActionActive{ false }, m_isMoving{ false } {}

bool PickUp::IsMoving() const
{
	return m_isMoving;
}

bool PickUp::IsActionActive() const
{
	return m_isActionActive;
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