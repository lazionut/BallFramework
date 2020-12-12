#include "PickUpActions.h"

void PickUpActions::SpeedUp()
{
	Time::SetTimeScale(2);
}

void PickUpActions::SlowDown()
{
	Time::SetTimeScale(1);
}

void PickUpActions::SmallerPaddle(Paddle& paddle)
{
	paddle.SetWidth(paddle.GetWidth() - 2);
}

void PickUpActions::BiggerPaddle(Paddle& paddle)
{
	paddle.SetWidth(paddle.GetWidth() + 2);
}

void PickUpActions::FasterPaddle(Paddle& paddle, float speed)
{
	paddle.SetSpeed(paddle.GetSpeed() + speed);
}

void PickUpActions::SlowerPaddle(Paddle& paddle, float speed)
{
	paddle.SetSpeed(paddle.GetSpeed() - speed);
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
	ball.AddSpeed(-speed);
}

void PickUpActions::BonusPoints(Score& score, int points)
{
	score.AddPoints(points);
}

void PickUpActions::RemovePoints(Score& score, int points)
{
	score.AddPoints(-points);
}

