#include "PickUp.h"

namespace BallFramework
{

	void PickUp::InvokeAction()
	{
		m_isMoving = false;
		m_isActionActive = true;

		if (m_startAction)
		{
			m_startAction();
		}
	}

	bool PickUp::ContinueAction()
	{
		m_time += Time::GetUnscaledDeltaTime();

		if (m_time >= m_StopTime)
		{
			if (m_StopAction)
			{
				m_StopAction();
				m_isActionActive = false;
				return true;
			}
		}
		return false;
	}

	void PickUp::StartMoving()
	{
		m_isMoving = true;
	}

	PickUp::PickUp() noexcept : m_time{ 0 }, m_StopTime{ 0 }, m_isActionActive{ false }, m_isMoving{ false } {}

	PickUp::PickUp(std::function<void()> startAction, const Vector2& position, const float size, const Vector2& direction, float speed) noexcept
		: Ball(position, size, direction, speed),
		m_startAction{ startAction }, m_time{ 0 }, m_StopTime{ 0 }, m_isActionActive{ false }, m_isMoving{ false } {}

	PickUp::PickUp(std::function<void()> startAction, std::function<void()> stopAction) noexcept
		: m_startAction{ startAction }, m_StopAction{ stopAction }, m_time{ 0 },
		m_StopTime{ 0 }, m_isActionActive{ false }, m_isMoving{ false } {}

	bool PickUp::IsMoving() const noexcept
	{
		return m_isMoving;
	}

	bool PickUp::IsActionActive() const noexcept
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

	void PickUp::SetActions(std::function<void()> startAction, std::function<void()> stopAction, float time)
	{
		m_StopTime = time;
		m_startAction = startAction;
		m_StopAction = stopAction;
	}

}