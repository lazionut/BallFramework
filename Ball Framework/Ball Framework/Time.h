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
		std::chrono::time_point<std::chrono::system_clock> last;
		std::chrono::time_point<std::chrono::system_clock> now;

		TimeAux();

		void resetTime();

	public:
		TimeAux(const TimeAux&) = delete;
		TimeAux& operator=(const TimeAux&) = delete;

		friend class Time;
	};

	static TimeAux aux;

	Time();

public:
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;

	static void resetTime();
	static void updateTime();
	static void updateDone();
	static double getRealDelta();
	static double getTimeSinceStartUp();
	static double getDeltaTime();
	static double getRealTime();
};