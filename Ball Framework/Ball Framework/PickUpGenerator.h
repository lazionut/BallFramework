#pragma once

#include "PickUp.h"
#include "PickUpActions.h"

class PickUpGenerator
{
public:

	enum class Actions : uint8_t
	{
		SPEEDCHANGE,

		PADDLESIZECHANGE,
		PADDLESPEEDCHANGE,

		BALLSIZECHANGE,
		BALLSPEEDCHANGE,

		BONUSPOINTS,

		REMOVEPOINTS,

		//numarul de actiuni
		ACTIONSNUMBER
	};

	Actions GetPickUpType();

	PickUp CreateSpeedPickUp();
	PickUp CreatePaddleSizeChangePickUp(Paddle& paddle, float difference);
	PickUp CreatePaddleSpeedChangePickUp(Paddle& paddle, float speed);
	PickUp CreateBallSizeChangePickUp(Ball& ball, float difference);

};

