#include "PickUpGenerator.h"

namespace BallFramework
{

	PickUpGenerator::PickUpGenerator(std::vector<Score>& scoreList) noexcept
		: m_pickUp{}, m_actionTime{ 0.0f }, m_paddleAxis{ Vector2::zero },
		m_scoreList{ scoreList } {}

	PickUp PickUpGenerator::CreateEmptyPickUp(const Vector2& postion) const noexcept
	{
		return PickUp(m_pickUp);
	}

	Actions PickUpGenerator::GetPickUpType()
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

	void PickUpGenerator::SetGeneratorData(const GeneratorData& data) noexcept
	{
		m_data = data;
	}

	void PickUpGenerator::SetActions(PickUp& pickUp, GameObject* object)
	{
		switch (pickUp.m_actionType)
		{
		case Actions::SPEEDCHANGE:
			SetSpeedActions(pickUp);
			break;
		case Actions::PADDLESIZECHANGE:
			if (auto paddle = dynamic_cast<Paddle*>(object); paddle != nullptr)
			{
				SetPaddleSizeChangeActions(pickUp, *paddle);
			}
			break;
		case Actions::PADDLESPEEDCHANGE:
			if (auto paddle = dynamic_cast<Paddle*>(object); paddle != nullptr)
			{
				SetPaddleSpeedChangeActions(pickUp, *paddle);
			}
			break;
		case Actions::BALLSIZECHANGE:
			if (auto ball = dynamic_cast<Ball*>(object); ball != nullptr)
			{
				SetBallSizeChangeActions(pickUp, *ball);
			}
			break;
		case Actions::BALLSPEEDCHANGE:
			if (auto ball = dynamic_cast<Ball*>(object); ball != nullptr)
			{
				SetBallSpeedChangeActions(pickUp, *ball);
			}
			break;
		case Actions::BONUSPOINTS:
			SetBonusPointsActions(pickUp);
			break;
		case Actions::REMOVEPOINTS:
			SetRemovePointsActions(pickUp);
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
		Vector2 sizeDifference = m_paddleAxis * m_data.paddleSizeChange;

		pickUp.SetActions
		(
			[&paddle, sizeDifference]() -> void { PickUpActions::BiggerPaddle(paddle, sizeDifference); },
			[&paddle, sizeDifference]() -> void { PickUpActions::SmallerPaddle(paddle, sizeDifference); },
			m_actionTime
		);
	}

	void PickUpGenerator::SetPaddleSpeedChangeActions(PickUp& pickUp, Paddle& paddle)
	{
		pickUp.SetActions
		(
			[&paddle, this]() -> void { PickUpActions::FasterPaddle(paddle, m_data.paddleSpeedChange); },
			[&paddle, this]() -> void { PickUpActions::SlowerPaddle(paddle, m_data.paddleSpeedChange); },
			m_actionTime
		);
	}

	void PickUpGenerator::SetBallSizeChangeActions(PickUp& pickUp, Ball& ball)
	{
		pickUp.SetActions
		(
			[&ball, this]() -> void { PickUpActions::BiggerBall(ball, m_data.ballSizeChange); },
			[&ball, this]() -> void { PickUpActions::SmallerBall(ball, m_data.ballSizeChange); },
			m_actionTime
		);
	}

	void PickUpGenerator::SetBallSpeedChangeActions(PickUp& pickUp, Ball& ball)
	{
		pickUp.SetActions
		(
			[&ball, this]() -> void { PickUpActions::FasterBall(ball, m_data.ballSpeedChange); },
			[&ball, this]() -> void { PickUpActions::SlowerBall(ball, m_data.ballSpeedChange); },
			m_actionTime
		);
	}

	void PickUpGenerator::SetBonusPointsActions(PickUp& pickUp)
	{
		pickUp.SetActions
		(
			[this]() -> void { PickUpActions::BonusPoints(m_scoreList[Random::Range(m_scoreList.size())], m_data.maxPointsDif); },
			nullptr
		);
	}

	void PickUpGenerator::SetRemovePointsActions(PickUp& pickUp)
	{
		pickUp.SetActions
		(
			[this]() -> void { PickUpActions::RemovePoints(m_scoreList[Random::Range(m_scoreList.size())], m_data.maxPointsDif); },
			nullptr
		);
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

#pragma region GeneratorData
	GeneratorData::GeneratorData() noexcept
		: GeneratorData(0, 0, 0, 0, 0, 0) {}

	GeneratorData::GeneratorData(float paddleSizeChange, float paddleSpeedChange, float ballSizeChange,
		float ballSpeedChange, float timeChange, int maxPointsDif) noexcept
		: paddleSizeChange{ paddleSizeChange }, paddleSpeedChange{ paddleSpeedChange }, ballSizeChange{ ballSizeChange },
		ballSpeedChange{ ballSpeedChange }, timeChange{ timeChange }, maxPointsDif{ maxPointsDif } {}

	void GeneratorData::Set(float paddleSizeChange, float paddleSpeedChange, float ballSizeChange,
		float ballSpeedChange, float timeChange, int maxPointsDif) noexcept
	{
		this->paddleSizeChange = paddleSizeChange;
		this->paddleSpeedChange = paddleSpeedChange;
		this->ballSizeChange = ballSizeChange;
		this->ballSpeedChange = ballSpeedChange;
		this->timeChange = timeChange;
		this->maxPointsDif = maxPointsDif;
	}
#pragma endregion
}