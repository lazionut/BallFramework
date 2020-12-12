#pragma once
#include "Ball.h"
#include "Paddle.h"
#include "Score.h"

class PickUpActions
{
public:
	static void SpeedUp();
	static void SlowDown();

	static void SmallerPaddle(Paddle& paddle);
	static void BiggerPaddle(Paddle& paddle);

	static void FasterPaddle(Paddle& paddle, float speed);
	static void SlowerPaddle(Paddle& paddle, float speed);

	static void BiggerBall(Ball& ball, float x);
	static void SmallerBall(Ball& ball, float x);

	static void FasterBall(Ball& ball, float speed);
	static void SlowerBall(Ball& ball, float speed);

	static void BonusPoints(Score& score, int points);

	static void RemovePoints(Score& score, int points);
};