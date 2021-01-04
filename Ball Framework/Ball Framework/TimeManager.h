#pragma once
#include <chrono>
#include "Time.h"

using namespace std::chrono;

class TimeManager
{
private:
	double m_realDelta;

	time_point<system_clock> m_last;
	time_point<system_clock> m_now;

public:
	TimeManager();

	void ResetTime();
	void UpdateTime();
	void UpdateDone();

	double GetRealDelta();
};

