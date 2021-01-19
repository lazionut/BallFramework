#pragma once
#include "Ball.h"
#include "Paddle.h"
#include "Score.h"

namespace BallFramework
{
	class PickUpActions
	{
	public:

		static void SpeedUp();
		static void SlowDown();

		static void BiggerPaddle(Paddle& paddle, const Vector2& difference);
		static void SmallerPaddle(Paddle& paddle, const Vector2& difference);

		static void FasterPaddle(Paddle& paddle, float speed);
		static void SlowerPaddle(Paddle& paddle, float speed);

		static void BiggerBall(Ball& ball, float x);
		static void SmallerBall(Ball& ball, float x);

		static void FasterBall(Ball& ball, float speed);
		static void SlowerBall(Ball& ball, float speed);

		static void BonusPoints(Score& score, int points);

		static void RemovePoints(Score& score, int points);
	};

}