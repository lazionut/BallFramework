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