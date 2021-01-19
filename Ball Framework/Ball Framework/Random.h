#pragma once
#include <random>
#include <chrono>

namespace BallFramework
{
	class Random
	{
	public:

		static int Range(int lower, int upper);
		static int Range(int upper);
		static bool CoinFlip() noexcept;

		template<class S>
		static void SetSeed(S&& seed);
		static void SetRandomSeed();

	private:
		static std::mt19937 s_generator;
	};

	template<class S>
	inline void Random::SetSeed(S&& seed)
	{
		s_generator.seed(seed);
	}
}