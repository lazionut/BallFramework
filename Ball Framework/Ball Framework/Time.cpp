#include "Time.h"

namespace BallFramework
{

	double Time::s_deltaTime = 0.0;
	double Time::s_timeSinceStart = 0.0;
	double Time::s_realTime = 0.0;
	double Time::s_gameTime = 0.0;
	double Time::s_scaledTimeSinceStart = 0.0;
	double Time::s_unscaledDelta = 0.0;
	float  Time::s_timeScale = 1.0f;

	double Time::GetTimeSinceStartUp() noexcept
	{
		return s_timeSinceStart;
	}

	double Time::GetDeltaTime() noexcept
	{
		return s_deltaTime;
	}

	double Time::GetRealTime() noexcept
	{
		return s_realTime;
	}

	double Time::GetUnscaledDeltaTime() noexcept
	{
		return s_unscaledDelta;
	}

	double Time::GetScaledTimeSinceStart() noexcept
	{
		return s_scaledTimeSinceStart;
	}

	float Time::GetTimeScale() noexcept
	{
		return s_timeScale;
	}

	void Time::SetTimeScale(float timeScale) noexcept
	{
		if (timeScale >= 0.0f)
		{
			Time::s_timeScale = timeScale;
		}
	}

}