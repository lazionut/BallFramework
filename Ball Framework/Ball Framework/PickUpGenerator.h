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

	const PickUp& CreateSpeedPickUp();
	const PickUp& CreatePaddleSizeChangePickUp(Paddle& paddle, float difference);
	const PickUp& CreatePaddleSpeedChangePickUp(Paddle& paddle, float speed);
	const PickUp& CreateBallSizeChangePickUp(Ball& ball, float difference);
	const PickUp& CreateBallSpeedChangePickUp(Ball& ball, float speed);
	const PickUp& CreateBonusPointsPickUp(Score& score, uint16_t points);
	const PickUp& CreateRemovePointsPickUp(Score& score, uint16_t points);

	void SetDefaultProperties(const float size, const float speed);

	PickUpGenerator() = default;
	PickUpGenerator(const float size, const float speed);

private:
	PickUp m_pickUp;
};

