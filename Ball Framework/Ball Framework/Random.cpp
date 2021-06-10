#include "Random.h"

namespace BallFramework
{
	int Random::Range(int lower, int upper) noexcept
	{
		return s_generator() % (upper - lower) + lower;
	}

	int Random::Range(int upper) noexcept
	{
		return s_generator() % upper;
	}

	bool Random::CoinFlip() noexcept
	{
		return (s_generator() % 100) >= 50;
	}

	void Random::SetRandomSeed()
	{
		s_generator.seed(static_cast<unsigned int>(time(nullptr)));

		std::seed_seq seed_seq{ s_generator(), s_generator(), 
			s_generator(), s_generator(), s_generator(), s_generator() };

		s_generator.seed(seed_seq);
	}
}