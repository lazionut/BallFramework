#include "Time.h"

Time::TimeAux::TimeAux()
	: deltaTime{ 0.0 }, realTime{ 0.0 }, realDelta{ 0.0 }, timeSinceStart{ 0.0 },
	timeScale{ 1.0f }, unscaledDelta{ 0.0 }, scaledTimeSinceStart{ 0.0 }, gameTime{ 0.0 },
	now{ std::chrono::system_clock::now() },
	last{ std::chrono::system_clock::now() } {}

void Time::TimeAux::resetTime()
{
	realTime = 0.0;
	deltaTime = 0.0;
	realDelta = 0.0;
	gameTime = 0.0;
	unscaledDelta = 0.0;
	timeScale = 1.0f;
}

Time::TimeAux Time::aux;

void Time::resetTime()
{
	aux.resetTime();
}

void Time::updateTime()
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

void Time::updateDone()
{
	aux.deltaTime = 0.0;
	aux.unscaledDelta = 0.0;
}

double Time::getRealDelta()
{
	return aux.realDelta;
}

double Time::getTimeSinceStartUp()
{
	return aux.timeSinceStart;
}

double Time::getDeltaTime()
{
	return aux.deltaTime;
}

double Time::getRealTime()
{
	return aux.realTime;
}

double Time::getUnscladeDeltaTime()
{
	return aux.unscaledDelta;
}

double Time::getScaledTimeSinceStart()
{
	return aux.scaledTimeSinceStart;
}

float Time::getTimeScale()
{
	return aux.timeScale;
}

void Time::setTimeScale(float timeScale)
{
	if (timeScale >= 0.0f)
	{
		aux.timeScale = timeScale;
	}
}
