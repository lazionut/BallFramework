#pragma once
#include <functional>
#include <thread>
#include "Vector2.h"
#include "Time.h"
#include "Paddle.h"
#include "Ball.h"

class PickUp
{
public:
	PickUp();
	PickUp(std::function<void()> startAction, const Vector2& position, const Vector2& dimension, const Vector2& direction, float speed);
	PickUp(std::function<void()> startAction, std::function<void()> stopAction);

	Vector2 GetPosition() const;
	Vector2 GetDimension() const;
	Vector2 GetDirection() const;
	float GetSpeed() const;

	void SetPosition(const Vector2& position);
	void SetDimension(const Vector2& dimension);
	void SetDirection(const Vector2& direction);
	void SetSpeed(float speed);
	void SetStartAction(std::function<void()> action);
	void SetStopAction(std::function<void()> action);
	void SetActions(std::function<void()> startAction, std::function<void()> stopAction);
	void Set(const Vector2& position, const Vector2& dimension, const Vector2& direction, float speed);

	static void SpeedUp();
	static void SlowDown();
	static void SmallerPaddle(Paddle& paddle);
	static void BiggerPaddle(Paddle& paddle);
	static void BiggerBall(Ball& ball, float x);
	static void SmallerBall(Ball& ball, float x);

	void InvokeAction(float time = 0.0f);
	void Move();
	void ContinueAction();

private:

	void StopAction();

	std::function<void()> m_startAction;
	std::function<void()> m_StopAction;
	Vector2 m_position, m_dimension, m_direction;
	float m_speed;
	float m_time;
};

