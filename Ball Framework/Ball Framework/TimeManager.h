#pragma once
#include <chrono>
#include "Time.h"

class TimeManager
{
private:
	double m_realDelta;

	std::chrono::time_point<std::chrono::system_clock> m_last;
	std::chrono::time_point<std::chrono::system_clock> m_now;

	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;
public:
	TimeManager();

	void ResetTime();
	void UpdateTime();
	void UpdateDone();

	double GetRealDelta();
};

