#include "Time.h"

Time::TimeAux::TimeAux()
	: deltaTime{ 0.0 }, realTime{ 0.0 }, realDelta{ 0.0 }, timeSinceStart{ 0.0 },
	timeScale{ 1.0f }, unscaledDelta{ 0.0 }, scaledTimeSinceStart{ 0.0 }, gameTime{ 0.0 },
	now{ std::chrono::system_clock::now() },
	last{ std::chrono::system_clock::now() } {}

void Time::TimeAux::ResetTime()
{
	realTime = 0.0;
	deltaTime = 0.0;
	realDelta = 0.0;
	gameTime = 0.0;
	unscaledDelta = 0.0;
	timeScale = 1.0f;
}

Time::TimeAux Time::aux;

void Time::ResetTime()
{
	aux.ResetTime();
}

void Time::UpdateTime()
{
	aux.now = std::chrono::system_clock::now();

	std::chrono::duration<double> dif = aux.now - aux.last;
	aux.realDelta = dif.count();
	aux.unscaledDelta += aux.realDelta;
	aux.deltaTime += (aux.realDelta * aux.timeScale);
	aux.realTime += aux.realDelta;
	aux.gameTime += (aux.realDelta * aux.timeScale);
	aux.timeSinceStart += aux.realDelta;
	aux.scaledTimeSinceStart += (aux.realDelta * aux.timeScale);

	aux.last = aux.now;
}

void Time::UpdateDone()
{
	aux.deltaTime = 0.0;
	aux.unscaledDelta = 0.0;
}

double Time::GetRealDelta()
{
	return aux.realDelta;
}

double Time::GetTimeSinceStartUp()
{
	return aux.timeSinceStart;
}

double Time::GetDeltaTime()
{
	return aux.deltaTime;
}

double Time::GetRealTime()
{
	return aux.realTime;
}

double Time::GetUnscaledDeltaTime()
{
	return aux.unscaledDelta;
}

double Time::GetScaledTimeSinceStart()
{
	return aux.scaledTimeSinceStart;
}

float Time::GetTimeScale()
{
	return aux.timeScale;
}

void Time::SetTimeScale(float timeScale)
{
	if (timeScale >= 0.0f)
	{
		aux.timeScale = timeScale;
	}
}