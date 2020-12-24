#include "PickUpGenerator.h"

PickUpGenerator::Actions PickUpGenerator::GetPickUpType()
{
	return static_cast<Actions>(rand() % static_cast<int>(Actions::ACTIONSNUMBER));
}

const PickUp& PickUpGenerator::CreateSpeedPickUp()
{
	m_pickUp.SetActions(PickUpActions::SpeedUp, PickUpActions::SlowDown);

	return m_pickUp;
}

const PickUp& PickUpGenerator::CreatePaddleSizeChangePickUp(Paddle& paddle, float difference)
{
	m_pickUp.SetActions
	(
		[&]() -> void { PickUpActions::BiggerPaddle(paddle, difference); },
		[&]() -> void { PickUpActions::SmallerPaddle(paddle, difference); }
	);

	return m_pickUp;
}

const PickUp& PickUpGenerator::CreatePaddleSpeedChangePickUp(Paddle& paddle, float speed)
{
	m_pickUp.SetActions
	(
		[&]() -> void { PickUpActions::FasterPaddle(paddle, speed); },
		[&]() -> void { PickUpActions::SmallerPaddle(paddle, speed); }
	);

	return m_pickUp;
}

const PickUp& PickUpGenerator::CreateBallSizeChangePickUp(Ball& ball, float difference)
{
	m_pickUp.SetActions
	(
		[&]() -> void { PickUpActions::BiggerBall(ball, difference); },
		[&]() -> void { PickUpActions::SmallerBall(ball, difference); }
	);

	return m_pickUp;
}

const PickUp& PickUpGenerator::CreateBallSpeedChangePickUp(Ball& ball, float speed)
{
	m_pickUp.SetActions
	(
		[&]() -> void { PickUpActions::FasterBall(ball, speed); },
		[&]() -> void { PickUpActions::SlowerBall(ball, speed); }
	);

	return m_pickUp;
}

const PickUp& PickUpGenerator::CreateBonusPointsPickUp(Score& score, uint16_t points)
{
	m_pickUp.SetActions
	(
		[&]() -> void { PickUpActions::BonusPoints(score, points); },
		nullptr
	);

	return m_pickUp;
}

const PickUp& PickUpGenerator::CreateRemovePointsPickUp(Score& score, uint16_t points)
{
	m_pickUp.SetActions
	(
		[&]() -> void { PickUpActions::RemovePoints(score, points); },
		nullptr
	);

	return m_pickUp;
}

void PickUpGenerator::SetDefaultProperties(const Vector2& size, const float speed)
{
	m_pickUp.SetDimension(size);
	m_pickUp.SetSpeed(speed);
}

PickUpGenerator::PickUpGenerator(const Vector2& size, const float speed)
{
	SetDefaultProperties(size, speed);
}
