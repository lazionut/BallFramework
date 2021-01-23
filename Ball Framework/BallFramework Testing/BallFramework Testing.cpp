#include "pch.h"
#include "CppUnitTest.h"
#include "..\Ball Framework\Random.cpp"
#include "..\Ball Framework\PlayerEntry.cpp"

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

		TEST_METHOD(Test)
		{
			PlayerEntry playerExample("PlayerName");
			std::string name = playerExample.GetPlayerName();
			std::string expectedName = "PlayerName";

			Assert::AreEqual(name, expectedName);
		}

	};

}