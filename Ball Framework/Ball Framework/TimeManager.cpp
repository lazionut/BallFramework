#include "TimeManager.h"

TimeManager::TimeManager()
    : realDelta{ 0.0 }, now{ std::chrono::system_clock::now() }, last{ std::chrono::system_clock::now() } {}

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
    now = std::chrono::system_clock::now();

    std::chrono::duration<double> dif = now - last;
    realDelta = dif.count();
    double scaledDelta = realDelta * Time::GetTimeScale();

    Time::s_deltaTime += scaledDelta;
    Time::s_unscaledDelta += realDelta;
    Time::s_gameTime += scaledDelta;
    Time::s_realTime += realDelta;
    Time::s_scaledTimeSinceStart += scaledDelta;
    Time::s_timeSinceStart += realDelta;

    last = now;
}

void TimeManager::UpdateDone()
{
    Time::s_deltaTime = 0.0;
    Time::s_unscaledDelta = 0.0;
}

double TimeManager::GetRealDelta()
{
    return realDelta;
}
