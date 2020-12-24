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
	PickUp CreateBallSpeedChangePickUp(Ball& ball, float speed);
	PickUp CreateBonusPointsPickUp(Score& score, uint16_t points);
	PickUp CreateRemovePointsPickUp(Score& score, uint16_t points);

	void SetDefaultProperties(const Vector2& size, const float speed);

	PickUpGenerator() = default;
	PickUpGenerator(const Vector2& size, const float speed);

private:
	PickUp m_pickUp;
};

