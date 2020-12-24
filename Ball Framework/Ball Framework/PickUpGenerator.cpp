#include "PickUpGenerator.h"

PickUpGenerator::Actions PickUpGenerator::GetPickUpType()
{
	return static_cast<Actions>(rand() % static_cast<int>(Actions::ACTIONSNUMBER));
}

PickUp PickUpGenerator::CreateSpeedPickUp()
{
	m_pickUp.SetActions(PickUpActions::SpeedUp, PickUpActions::SlowDown);

	return m_pickUp;
}

PickUp PickUpGenerator::CreatePaddleSizeChangePickUp(Paddle& paddle, float difference)
{
	m_pickUp.SetActions
	(
		[&]() -> void { PickUpActions::BiggerPaddle(paddle, difference); },
		[&]() -> void { PickUpActions::SmallerPaddle(paddle, difference); }
	);

	return m_pickUp;
}

PickUp PickUpGenerator::CreatePaddleSpeedChangePickUp(Paddle& paddle, float speed)
{
	m_pickUp.SetActions
	(
		[&]() -> void { PickUpActions::FasterPaddle(paddle, speed); },
		[&]() -> void { PickUpActions::SmallerPaddle(paddle, speed); }
	);

	return m_pickUp;
}

PickUp PickUpGenerator::CreateBallSizeChangePickUp(Ball& ball, float difference)
{
	return
	{
		[&ball, difference]() { PickUpActions::BiggerBall(ball, difference); },
		[&ball, difference]() { PickUpActions::SmallerBall(ball, difference); }
	};
}

PickUp PickUpGenerator::CreateBallSpeedChangePickUp(Ball& ball, float speed)
{
	return
	{
		[&ball, speed]() { PickUpActions::FasterBall(ball, speed); },
		[&ball, speed]() { PickUpActions::SlowerBall(ball, speed); }
	};
}

PickUp PickUpGenerator::CreateBonusPointsPickUp(Score& score, uint16_t points)
{
	return
	{
		[&score, points]() { PickUpActions::BonusPoints(score, points); },
		nullptr
	};
}

PickUp PickUpGenerator::CreateRemovePointsPickUp(Score& score, uint16_t points)
{
	return
	{
		[&score, points]() { PickUpActions::RemovePoints(score, points); },
		nullptr
	};
}

void PickUpGenerator::SetDefaultProperties(const Vector2& size, const float speed)
{
	m_pickUp.SetDimension(size);
	m_pickUp.SetSpeed(speed);
}

PickUpGenerator::PickUpGenerator(const Vector2& size, const float speed)
{
	m_pickUp.SetDimension(size);
	m_pickUp.SetSpeed(speed);
}
