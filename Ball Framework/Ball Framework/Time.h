#pragma once
#include <chrono>

namespace BallFramework
{

	class Time
	{
	public:
		friend class TimeManager;

		static double GetTimeSinceStartUp() noexcept;
		static double GetDeltaTime() noexcept;
		static double GetRealTime() noexcept;
		static double GetUnscaledDeltaTime() noexcept;
		static double GetScaledTimeSinceStart() noexcept;
		static float GetTimeScale() noexcept;
		static void SetTimeScale(float timeScale) noexcept;

	private:
		static double s_deltaTime;
		static double s_timeSinceStart;
		static double s_realTime;
		static double s_gameTime;
		static double s_scaledTimeSinceStart;
		static double s_unscaledDelta;
		static float s_timeScale;

		Time() = delete;
	};

}