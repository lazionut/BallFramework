#include "TimeManager.h"

TimeManager::TimeManager()
    : realDelta{ 0.0 }, now{ std::chrono::system_clock::now() }, last{ std::chrono::system_clock::now() } {}

void TimeManager::ResetTime()
{
    Time::deltaTime = 0.0;
    Time::unscaledDelta = 0.0;
    Time::realTime = 0.0;
    Time::gameTime = 0.0;
    Time::timeScale = 1.0f;
}

void TimeManager::UpdateTime()
{
    now = std::chrono::system_clock::now();

    std::chrono::duration<double> dif = now - last;
    realDelta = dif.count();
    double scaledDelta = realDelta * Time::GetTimeScale();

    Time::deltaTime += scaledDelta;
    Time::unscaledDelta += realDelta;
    Time::gameTime += scaledDelta;
    Time::realTime += realDelta;
    Time::scaledTimeSinceStart += scaledDelta;
    Time::timeSinceStart += realDelta;

    last = now;
}

void TimeManager::UpdateDone()
{
    Time::deltaTime = 0.0;
    Time::unscaledDelta = 0.0;
}

double TimeManager::GetRealDelta()
{
    return realDelta;
}
