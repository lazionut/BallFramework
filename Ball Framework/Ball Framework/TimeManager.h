#pragma once

#include <chrono>
#include "Time.h"

namespace BallFramework
{

	using namespace std::chrono;

	class TimeManager
	{
	private:
		double m_realDelta;

		time_point<system_clock> m_last;
		time_point<system_clock> m_now;

	public:
		TimeManager() noexcept;

		void ResetTime() noexcept;
		void UpdateTime() noexcept;
		void UpdateDone() noexcept;

		double GetRealDelta() const noexcept;
	};

}