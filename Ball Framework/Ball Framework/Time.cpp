#include "Time.h"

Time::TimeAux::TimeAux()
	: deltaTime{ 0.0 }, realTime{ 0.0 }, realDelta{ 0.0 }, timeSinceStart{ 0.0 },
	now{ std::chrono::system_clock::now() },
	last{ std::chrono::system_clock::now() } {}

void Time::TimeAux::resetTime()
{
	realTime = 0.0;
	deltaTime = 0.0;
	realDelta = 0.0;
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
	aux.deltaTime += aux.realDelta;
	aux.realTime += aux.realDelta;
	aux.timeSinceStart += aux.realDelta;

	aux.last = aux.now;
}

void Time::updateDone()
{
	aux.deltaTime = 0.0;
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