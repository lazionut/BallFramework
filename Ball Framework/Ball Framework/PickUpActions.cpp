#include "PickUpActions.h"

namespace BallFramework
{

	void PickUpActions::SpeedUp()
	{
		Time::SetTimeScale(2);
	}

	void PickUpActions::SlowDown()
	{
		Time::SetTimeScale(1);
	}

	void PickUpActions::SmallerPaddle(Paddle& paddle, const Vector2& difference)
	{
		paddle.DecreaseSize(difference);
	}

	void PickUpActions::BiggerPaddle(Paddle& paddle, const Vector2& difference)
	{
		paddle.AddSize(difference);
	}

	void PickUpActions::FasterPaddle(Paddle& paddle, float speed)
	{
		paddle.AddSpeed(speed);
	}

	void PickUpActions::SlowerPaddle(Paddle& paddle, float speed)
	{
		paddle.DecreaseSpeed(speed);
	}

	void PickUpActions::BiggerBall(Ball& ball, float x)
	{
		ball.SetSize(ball.GetSize() + 1);
	}

	void PickUpActions::SmallerBall(Ball& ball, float x)
	{
		ball.SetSize(ball.GetSize() - 1);
	}

	void PickUpActions::FasterBall(Ball& ball, float speed)
	{
		ball.AddSpeed(speed);
	}

	void PickUpActions::SlowerBall(Ball& ball, float speed)
	{
		ball.DecreaseSpeed(speed);
	}

	void PickUpActions::BonusPoints(Score& score, int points)
	{
		score.AddPoints(points);
	}

	void PickUpActions::RemovePoints(Score& score, int points)
	{
		score.AddPoints(-points);
	}

}