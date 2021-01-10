#include "TimeManager.h"

namespace BallFramework
{

	TimeManager::TimeManager()
		: m_realDelta{ 0.0 }, m_now{ system_clock::now() }, m_last{ system_clock::now() } {}

	void TimeManager::ResetTime()
	{
		Time::s_deltaTime = 0.0;
		Time::s_unscaledDelta = 0.0;
		Time::s_realTime = 0.0;
		Time::s_gameTime = 0.0;
		Time::s_timeScale = 1.0f;
	}

	void TimeManager::UpdateTime()
	{
		m_now = system_clock::now();

		duration<double> dif = m_now - m_last;
		m_realDelta = dif.count();
		double scaledDelta = m_realDelta * Time::GetTimeScale();

		Time::s_deltaTime += scaledDelta;
		Time::s_unscaledDelta += m_realDelta;
		Time::s_gameTime += scaledDelta;
		Time::s_realTime += m_realDelta;
		Time::s_scaledTimeSinceStart += scaledDelta;
		Time::s_timeSinceStart += m_realDelta;

		m_last = m_now;
	}

	void TimeManager::UpdateDone()
	{
		Time::s_deltaTime = 0.0;
		Time::s_unscaledDelta = 0.0;
	}

	double TimeManager::GetRealDelta()
	{
		return m_realDelta;
	}

}