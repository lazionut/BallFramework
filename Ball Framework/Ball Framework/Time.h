#pragma once
#include <chrono>

class Time
{
private:

	class TimeAux
	{
	private:
		double deltaTime;
		double realTime;
		std::chrono::time_point<std::chrono::system_clock> last;
		std::chrono::time_point<std::chrono::system_clock> now;

		TimeAux();

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

	static void updateTime();
	static double getDeltaTime();
	static double getRealTime();
};