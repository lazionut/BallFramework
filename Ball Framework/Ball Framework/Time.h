#pragma once
#include <chrono>

class Time
{
private:
	friend class TimeManager;

	static double deltaTime;
	static double timeSinceStart;
	static double realTime;
	static double gameTime;
	static double scaledTimeSinceStart;
	static double unscaledDelta;
	static float timeScale;

	Time();
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;

public:

	static double GetTimeSinceStartUp();
	static double GetDeltaTime();
	static double GetRealTime();
	static double GetUnscaledDeltaTime();
	static double GetScaledTimeSinceStart();
	static float GetTimeScale();
	static void SetTimeScale(float timeScale);
};