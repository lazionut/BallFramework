#include "PickUpGenerator.h"

namespace BallFramework
{
	PickUpGenerator::PickUpGenerator()
		: m_pickUp{}, m_actionTime{ 0.0f }, m_paddleAxis{ Vector2::zero },
		m_timeChange{ 0.0f }, m_maxPointsDif{ 0 } {}

	PickUpGenerator::PickUpGenerator(const Vector2& paddleSize, const float ballSize, const float speed, const float time)
	{
		SetPickUpDefaultProperties(paddleSize, ballSize, speed, time);
	}

	PickUp PickUpGenerator::CreateEmptyPickUp(const Vector2& postion) const noexcept
	{
		return PickUp();
	}

	PickUpGenerator::Actions PickUpGenerator::GetPickUpType()
	{
		return static_cast<Actions>(Random::Range(static_cast<int>(Actions::ACTIONSNUMBER)));
	}

	void PickUpGenerator::SetPickUpDefaultProperties(const Vector2& paddleSize, const float ballSize, const float speed, const float time) noexcept
	{
		m_actionTime = time;
		m_pickUp.SetSize(ballSize);
		m_pickUp.SetSpeed(speed);
		m_paddleAxis = paddleSize;
	}

	void PickUpGenerator::SetModifiersDefaultProperties(const float speedChange, const float timeChange, const float paddleSizeDifference, const int maxPointsDif) noexcept
	{
		//m_speedChange = speedChange;
		m_timeChange = timeChange;
		m_maxPointsDif = maxPointsDif;
	}

	void PickUpGenerator::SetActions(PickUp& pickUp, GameObject* object)
	{
		switch (static_cast<Actions>(pickUp.m_actionType))
		{
		case Actions::SPEEDCHANGE:
			break;
		case Actions::PADDLESIZECHANGE:
			break;
		case Actions::PADDLESPEEDCHANGE:
			break;
		case Actions::BALLSIZECHANGE:
			break;
		case Actions::BALLSPEEDCHANGE:
			break;
		case Actions::BONUSPOINTS:
			break;
		case Actions::REMOVEPOINTS:
			break;
		default:
			break;
		}
	}

#pragma region Actions Setters
	void PickUpGenerator::SetSpeedActions(PickUp& pickUp)
	{
		pickUp.SetActions
		(
			PickUpActions::SpeedUp,
			PickUpActions::SlowDown,
			m_actionTime
		);
	}

	void PickUpGenerator::SetPaddleSizeChangeActions(PickUp& pickUp, Paddle& paddle)
	{
		Vector2 sizeDifference = m_paddleAxis * m_paddleSizeChange;

		pickUp.SetActions
		(
			[&paddle, sizeDifference]() -> void { PickUpActions::BiggerPaddle(paddle, sizeDifference); },
			[&paddle, sizeDifference]() -> void { PickUpActions::SmallerPaddle(paddle, sizeDifference); },
			m_actionTime
		);
	}

	void PickUpGenerator::SetPaddleSpeedChangePickUp(PickUp& pickUp, Paddle& paddle)
	{
		pickUp.SetActions
		(
			[&paddle, this]() -> void { PickUpActions::FasterPaddle(paddle, m_paddleSpeedChange); },
			[&paddle, this]() -> void { PickUpActions::SlowerPaddle(paddle, m_paddleSpeedChange); },
			m_actionTime
		);
	}

	void PickUpGenerator::SetBallSizeChangeActions(PickUp& pickUp, Ball& ball)
	{
		pickUp.SetActions
		(
			[&ball, this]() -> void { PickUpActions::BiggerBall(ball, m_ballSizeChange); },
			[&ball, this]() -> void { PickUpActions::SmallerBall(ball, m_ballSizeChange); },
			m_actionTime
		);
	}

	void PickUpGenerator::SetBallSpeedChangeActions(PickUp& pickUp, Ball& ball)
	{
		pickUp.SetActions
		(
			[&ball, this]() -> void { PickUpActions::FasterBall(ball, m_ballSpeedChange); },
			[&ball, this]() -> void { PickUpActions::SlowerBall(ball, m_ballSpeedChange); },
			m_actionTime
		);
	}

	void PickUpGenerator::SetBonusPointsActions(PickUp& pickUp)
	{
		if (score != nullptr)
		{
			pickUp.SetActions
			(
				[this]() -> void { PickUpActions::BonusPoints(*score, m_maxPointsDif); },
				nullptr
			);
		}
	}

	void PickUpGenerator::SetRemovePointsActions(PickUp& pickUp)
	{
		if (score != nullptr)
		{
			pickUp.SetActions
			(
				[this]() -> void { PickUpActions::RemovePoints(*score, m_maxPointsDif); },
				nullptr
			);
		}
	}
#pragma endregion

#pragma region Create PickUps
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
		Vector2 sizeDifference = m_paddleAxis * difference;

		m_pickUp.SetActions
		(
			[&paddle, difference, sizeDifference]() -> void { PickUpActions::BiggerPaddle(paddle, sizeDifference); },
			[&paddle, difference, sizeDifference]() -> void { PickUpActions::SmallerPaddle(paddle, sizeDifference); },
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
#pragma endregion

}