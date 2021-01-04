#pragma once
#include <chrono>
#include "Time.h"

class TimeManager
{
private:
	double realDelta;

	std::chrono::time_point<std::chrono::system_clock> last;
	std::chrono::time_point<std::chrono::system_clock> now;

	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;
public:
	TimeManager();

	void ResetTime();
	void UpdateTime();
	void UpdateDone();

	double GetRealDelta();
};

