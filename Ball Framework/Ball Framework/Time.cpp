#include "Time.h"

double Time::deltaTime = 0.0;
double Time::timeSinceStart = 0.0;
double Time::realTime = 0.0;
double Time::gameTime = 0.0;
double Time::scaledTimeSinceStart = 0.0;
double Time::unscaledDelta = 0.0;
float  Time::timeScale = 1.0f;

double Time::GetTimeSinceStartUp()
{
	return timeSinceStart;
}

double Time::GetDeltaTime()
{
	return deltaTime;
}

double Time::GetRealTime()
{
	return realTime;
}

double Time::GetUnscaledDeltaTime()
{
	return unscaledDelta;
}

double Time::GetScaledTimeSinceStart()
{
	return scaledTimeSinceStart;
}

float Time::GetTimeScale()
{
	return timeScale;
}

void Time::SetTimeScale(float timeScale)
{
	if (timeScale >= 0.0f)
	{
		Time::timeScale = timeScale;
	}
}