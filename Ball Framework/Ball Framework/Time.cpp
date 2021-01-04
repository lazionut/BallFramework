#include "Time.h"

double Time::s_deltaTime = 0.0;
double Time::s_timeSinceStart = 0.0;
double Time::s_realTime = 0.0;
double Time::s_gameTime = 0.0;
double Time::s_scaledTimeSinceStart = 0.0;
double Time::s_unscaledDelta = 0.0;
float  Time::s_timeScale = 1.0f;

double Time::GetTimeSinceStartUp()
{
	return s_timeSinceStart;
}

double Time::GetDeltaTime()
{
	return s_deltaTime;
}

double Time::GetRealTime()
{
	return s_realTime;
}

double Time::GetUnscaledDeltaTime()
{
	return s_unscaledDelta;
}

double Time::GetScaledTimeSinceStart()
{
	return s_scaledTimeSinceStart;
}

float Time::GetTimeScale()
{
	return s_timeScale;
}

void Time::SetTimeScale(float timeScale)
{
	if (timeScale >= 0.0f)
	{
		Time::s_timeScale = timeScale;
	}
}