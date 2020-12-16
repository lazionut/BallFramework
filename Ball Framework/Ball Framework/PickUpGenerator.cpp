#include "PickUpGenerator.h"

PickUpGenerator::Actions PickUpGenerator::GetPickUpType()
{
	return static_cast<Actions>(rand() % static_cast<int>(Actions::ACTIONSNUMBER));
}

PickUp PickUpGenerator::CreateSpeedPickUp()
{
	return
	{
		PickUpActions::SpeedUp,
		PickUpActions::SlowDown
	};
}

PickUp PickUpGenerator::CreatePaddleSizeChangePickUp(Paddle& paddle, float difference)
{
	return
	{
		[&paddle, difference]() { PickUpActions::BiggerPaddle(paddle, difference); },
		[&paddle, difference]() { PickUpActions::SmallerPaddle(paddle, difference); }
	};
}

PickUp PickUpGenerator::CreatePaddleSpeedChangePickUp(Paddle& paddle, float speed)
{
	return
	{
		[&paddle, speed]() { PickUpActions::FasterPaddle(paddle, speed); },
		[&paddle, speed]() { PickUpActions::SmallerPaddle(paddle, speed); }
	};
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
