#pragma once
#include "PickUpActions.h"
#include "PickUp.h"
#include "Random.h"

namespace BallFramework
{
	class PickUpGenerator
	{
	public:
		PickUpGenerator();
		PickUpGenerator(const Vector2& paddleSize, const float ballSize, const float speed, const float time);

		PickUp CreateEmptyPickUp(const Vector2& postion) const noexcept;

		Actions GetPickUpType();
		void SetActions(PickUp& pickUp, GameObject* object);

		void SetSpeedActions(PickUp& pickUp);
		void SetPaddleSizeChangeActions(PickUp& pickUp, Paddle& paddle);
		void SetPaddleSpeedChangeActions(PickUp& pickUp, Paddle& paddle);
		void SetBallSizeChangeActions(PickUp& pickUp, Ball& ball);
		void SetBallSpeedChangeActions(PickUp& pickUp, Ball& ball);
		void SetBonusPointsActions(PickUp& pickUp);
		void SetRemovePointsActions(PickUp& pickUp);

		const PickUp& CreateSpeedPickUp();
		const PickUp& CreatePaddleSizeChangePickUp(Paddle& paddle, float difference);
		const PickUp& CreatePaddleSpeedChangePickUp(Paddle& paddle, float speed);
		const PickUp& CreateBallSizeChangePickUp(Ball& ball, float difference);
		const PickUp& CreateBallSpeedChangePickUp(Ball& ball, float speed);
		const PickUp& CreateBonusPointsPickUp(Score& score, uint16_t points);
		const PickUp& CreateRemovePointsPickUp(Score& score, uint16_t points);

		void SetPickUpDefaultProperties(const Vector2& paddleAxis, const float ballSize, const float speed, const float time) noexcept;
		void SetModifiersDefaultProperties(const float speedChange, const float timeChange, const float paddleSizeDifference, const int maxPointsDif) noexcept;

	private:
		PickUp m_pickUp;
		float m_actionTime;
		Vector2 m_paddleAxis;
		float m_paddleSizeChange;
		float m_paddleSpeedChange;
		float m_ballSizeChange;
		float m_ballSpeedChange;
		float m_timeChange;
		int m_maxPointsDif;
		Score* score;
	};
}