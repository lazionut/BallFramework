#pragma once
#include <chrono>

class Time
{
private:
	class TimeAux
	{
	private:
		double deltaTime;
		double realDelta;
		double timeSinceStart;
		double realTime;
		double gameTime;
		double scaledTimeSinceStart;
		double unscaledDelta;
		float timeScale;

		std::chrono::time_point<std::chrono::system_clock> last;
		std::chrono::time_point<std::chrono::system_clock> now;

		TimeAux();

		void ResetTime();

	public:
		TimeAux(const TimeAux&) = delete;
		TimeAux& operator=(const TimeAux&) = delete;

		friend class Time;
	};

	static TimeAux aux;

	Time();

	static void ResetTime();
	static void UpdateTime();
	static void UpdateDone();

	friend class Game;

public:
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;

	static double GetRealDelta();
	static double GetTimeSinceStartUp();
	static double GetDeltaTime();
	static double GetRealTime();
	static double GetUnscaledDeltaTime();
	static double GetScaledTimeSinceStart();
	static float GetTimeScale();
	static void SetTimeScale(float timeScale);
};