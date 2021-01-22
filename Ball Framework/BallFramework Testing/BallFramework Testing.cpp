#include "pch.h"
#include "CppUnitTest.h"
#include <SDL.h>
#include "..\Ball Framework\Ball.h"
#include "..\Ball Framework\Ball.cpp"
#include "..\Ball Framework\Paddle.cpp"
#include "..\Ball Framework\Paddle.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BallFramework
{

	TEST_CLASS(BallFrameworkTesting)
	{
	public:

		TEST_METHOD(BallPaddleCollisionTest)
		{
			Ball ball{ Vector2(0,0), 0.5f, Vector2(1,0), 5 };
			Paddle paddle;
			paddle.SetSize(Vector2(1, 1));
			paddle.SetPosition(Vector2(0, 0));
		}

	};
}