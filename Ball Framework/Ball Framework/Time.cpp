#include "Time.h"

Time::TimeAux::TimeAux()
	: deltaTime {0.0}, realTime {0.0}, now {std::chrono::system_clock::now()},
	last { std::chrono::system_clock::now() } {}

Time::TimeAux Time::aux;

void Time::updateTime()
{
	aux.now = std::chrono::system_clock::now();

	std::chrono::duration<double> dif = aux.now - aux.last;
	aux.deltaTime = dif.count();
	aux.realTime += aux.deltaTime;

	aux.last = aux.now;
}

double Time::getDeltaTime()
{
	return aux.deltaTime;
}

double Time::getRealTime()
{
	return aux.realTime;
}