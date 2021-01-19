#include "Random.h"

namespace BallFramework
{
	std::mt19937 Random::s_generator{};

	int Random::Range(int lower, int upper)
	{
		return s_generator() % (upper - lower) + lower;
	}

	int Random::Range(int upper)
	{
		return s_generator() % upper;
	}

	bool Random::CoinFlip() noexcept
	{
		return static_cast<bool>(s_generator() % 2);
	}

	void Random::SetRandomSeed()
	{
		s_generator.seed(static_cast<unsigned int>(time(nullptr)));
	}
}