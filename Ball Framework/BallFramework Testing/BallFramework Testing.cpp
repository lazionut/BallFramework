#include "pch.h"
#include "CppUnitTest.h"
#include "..\Ball Framework\Random.cpp"
#include "..\Ball Framework\PlayerEntry.cpp"
#include "..\Ball Framework\Score.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BallFramework
{

	TEST_CLASS(BallFrameworkTesting)
	{
	public:

		TEST_METHOD(RandomClassTest)
		{
			uint8_t randomChance = Random::CoinFlip();
			uint8_t isMinimumExpectedChance = 1;
			uint8_t isExpectedChance;

			if (randomChance >= 50)
				isExpectedChance = 1;

			Assert::AreEqual(isMinimumExpectedChance, isExpectedChance);
		}

		TEST_METHOD(PlayerEntryConstructorTest)
		{
			PlayerEntry playerExample("PlayerName");
			std::string name = playerExample.GetPlayerName();
			std::string expectedName = "PlayerName";

			Assert::AreEqual(name, expectedName);
		}

		TEST_METHOD(PongWinConditionTest)
		{
			Score score;
			score.AddPoints(5);
			uint8_t isWinScore;
			uint8_t isGameOver = 1;

			if (score.GetScore() == 5)
				isWinScore = 1;
		
			Assert::AreEqual(isWinScore, isGameOver);
		}

	};

}