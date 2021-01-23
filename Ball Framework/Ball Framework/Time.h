#pragma once
#include <chrono>

namespace BallFramework
{

	class Time
	{
	public:
		friend class TimeManager;

		static double GetTimeSinceStartUp();
		static double GetDeltaTime();
		static double GetRealTime();
		static double GetUnscaledDeltaTime();
		static double GetScaledTimeSinceStart();
		static float GetTimeScale();
		static void SetTimeScale(float timeScale);

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