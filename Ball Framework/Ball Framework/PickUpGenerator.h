#pragma once
#include "PickUpActions.h"
#include "PickUp.h"
#include "Random.h"

namespace BallFramework
{
	struct GeneratorData
	{
		float paddleSizeChange;
		float paddleSpeedChange;
		float ballSizeChange;
		float ballSpeedChange;
		float timeChange;
		int maxPointsDif;

		GeneratorData() noexcept;
		GeneratorData(float paddleSizeChange, float paddleSpeedChange, float ballSizeChange, 
			float ballSpeedChange, float timeChange, int maxPointsDif) noexcept;

		void Set(float paddleSizeChange, float paddleSpeedChange, float ballSizeChange, 
			float ballSpeedChange, float timeChange, int maxPointsDif) noexcept;
	};

	class PickUpGenerator
	{
	public:
		PickUpGenerator(std::vector<Score>& scoreList) noexcept;

		PickUp CreateEmptyPickUp(const Vector2& postion) const noexcept;

		Actions GetPickUpType();
		void SetActions(PickUp& pickUp, GameObject* object);

		void SetPickUpDefaultProperties(const Vector2& paddleAxis, const float ballSize, const float speed, const float time) noexcept;
		void SetGeneratorData(const GeneratorData& data) noexcept;

		const PickUp& CreateSpeedPickUp();
		const PickUp& CreatePaddleSizeChangePickUp(Paddle& paddle, float difference);
		const PickUp& CreatePaddleSpeedChangePickUp(Paddle& paddle, float speed);
		const PickUp& CreateBallSizeChangePickUp(Ball& ball, float difference);
		const PickUp& CreateBallSpeedChangePickUp(Ball& ball, float speed);
		const PickUp& CreateBonusPointsPickUp(Score& score, uint16_t points);
		const PickUp& CreateRemovePointsPickUp(Score& score, uint16_t points);

	private:
		void SetSpeedActions(PickUp& pickUp);
		void SetPaddleSizeChangeActions(PickUp& pickUp, Paddle& paddle);
		void SetPaddleSpeedChangeActions(PickUp& pickUp, Paddle& paddle);
		void SetBallSizeChangeActions(PickUp& pickUp, Ball& ball);
		void SetBallSpeedChangeActions(PickUp& pickUp, Ball& ball);
		void SetBonusPointsActions(PickUp& pickUp);
		void SetRemovePointsActions(PickUp& pickUp);

		PickUp m_pickUp;
		float m_actionTime;
		Vector2 m_paddleAxis;
		GeneratorData m_data;
		std::vector<Score>& m_scoreList;
	};
}