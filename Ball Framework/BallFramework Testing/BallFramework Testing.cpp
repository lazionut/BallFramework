#include "pch.h"
#include "CppUnitTest.h"
#include "..\Ball Framework\Random.cpp"
#include "..\Ball Framework\PlayerEntry.cpp"
#include "..\Ball Framework\Paths.cpp"
#include "..\Ball Framework\Vector2.cpp"
#include "..\Ball Framework\Colors.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BallFramework
{

	TEST_CLASS(BallFrameworkTesting)
	{
	public:

		TEST_METHOD(RandomRangeTest)
		{
			int randomChance = Random::Range(10, 20);
			int isRandomExpectedChance = 1;
			int isExpectedChance;

			if (randomChance >= 10 && randomChance < 20)
				isExpectedChance = 1;

			Assert::AreEqual(isRandomExpectedChance, isExpectedChance);
		}

		TEST_METHOD(PlayerEntryConstructorTest)
		{
			PlayerEntry playerExample("PlayerName");
			std::string name = playerExample.GetPlayerName();
			std::string expectedName = "PlayerName";

			Assert::AreEqual(name, expectedName);
		}

		TEST_METHOD(PathTest)
		{
			Logger::Initialize();
			Paths::SetFilePath("..\\Assets\\example");
			std::string pathExample = "..\\Assets\\example";
			std::string expectedPath = Paths::GetFilePath();

			Assert::AreNotSame(pathExample, expectedPath);
		}

		TEST_METHOD(Vector2LengthTest)
		{
			Vector2 vector;
			vector.Set(1, 2);
			float squaredLength = vector.GetLength();
			float length = vector.GetSquareLength();

			Assert::AreNotEqual(squaredLength, length);
		}

		TEST_METHOD(CustomColorTest)
		{
			Colors::AddCustomColor("colorExample", 100, 0, 10, 100);

			Assert::IsTrue(Colors::RemoveCustomColor("colorExample"));
		}

	};

}