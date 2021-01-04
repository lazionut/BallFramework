#include "PickUpGenerator.h"

PickUpGenerator::Actions PickUpGenerator::GetPickUpType()
{
	return static_cast<Actions>(rand() % static_cast<int>(Actions::ACTIONSNUMBER));
}

const PickUp& PickUpGenerator::CreateSpeedPickUp()
{
	m_pickUp.SetActions
	(
		PickUpActions::SpeedUp, 
		PickUpActions::SlowDown,
		m_actionTime
	);

	return m_pickUp;
}

const PickUp& PickUpGenerator::CreatePaddleSizeChangePickUp(Paddle& paddle, float difference)
{
	m_pickUp.SetActions
	(
		[&paddle, difference]() -> void { PickUpActions::BiggerPaddle(paddle, difference); },
		[&paddle, difference]() -> void { PickUpActions::SmallerPaddle(paddle, difference); },
		m_actionTime
	);

	return m_pickUp;
}

const PickUp& PickUpGenerator::CreatePaddleSpeedChangePickUp(Paddle& paddle, float speed)
{
	m_pickUp.SetActions
	(
		[&paddle, speed]() -> void { PickUpActions::FasterPaddle(paddle, speed); },
		[&paddle, speed]() -> void { PickUpActions::SlowerPaddle(paddle, speed); },
		m_actionTime
	);

	return m_pickUp;
}

const PickUp& PickUpGenerator::CreateBallSizeChangePickUp(Ball& ball, float difference)
{
	m_pickUp.SetActions
	(
		[&ball, difference]() -> void { PickUpActions::BiggerBall(ball, difference); },
		[&ball, difference]() -> void { PickUpActions::SmallerBall(ball, difference); },
		m_actionTime
	);

	return m_pickUp;
}

const PickUp& PickUpGenerator::CreateBallSpeedChangePickUp(Ball& ball, float speed)
{
	m_pickUp.SetActions
	(
		[&ball, speed]() -> void { PickUpActions::FasterBall(ball, speed); },
		[&ball, speed]() -> void { PickUpActions::SlowerBall(ball, speed); },
		m_actionTime
	);

	return m_pickUp;
}

const PickUp& PickUpGenerator::CreateBonusPointsPickUp(Score& score, uint16_t points)
{
	m_pickUp.SetActions
	(
		[&score, points]() -> void { PickUpActions::BonusPoints(score, points); },
		nullptr
	);

	return m_pickUp;
}

const PickUp& PickUpGenerator::CreateRemovePointsPickUp(Score& score, uint16_t points)
{
	m_pickUp.SetActions
	(
		[&score, points]() -> void { PickUpActions::RemovePoints(score, points); },
		nullptr
	);

	return m_pickUp;
}

void PickUpGenerator::SetDefaultProperties(const float size, const float speed, const float time)
{
	m_actionTime = time;
	m_pickUp.SetSize(size);
	m_pickUp.SetSpeed(speed);
}

PickUpGenerator::PickUpGenerator(const float size, const float speed, const float time)
{
	SetDefaultProperties(size, speed, time);
}
