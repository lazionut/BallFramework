#pragma once
#include <functional>
#include <thread>
#include "Vector2.h"
#include "Time.h"
#include "Paddle.h"
#include "Ball.h"

class PickUp : public Ball
{
public:

	PickUp();
	PickUp(std::function<void()> startAction, const Vector2& position, const float size, const Vector2& direction, float speed);
	PickUp(std::function<void()> startAction, std::function<void()> stopAction);

	bool IsMoving() const;
	bool IsActionActive() const;

	void SetStartAction(std::function<void()> action);
	void SetStopAction(std::function<void()> action);
	void SetActions(std::function<void()> startAction, std::function<void()> stopAction);

	void InvokeAction(float time = 0.0f);
	void ContinueAction();

	void StartMoving();

private:

	std::function<void()> m_startAction;
	std::function<void()> m_StopAction;
	float m_time;
	float m_StopTime;

	bool m_isActionActive;
	bool m_isMoving;
};

