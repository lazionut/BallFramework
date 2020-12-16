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
