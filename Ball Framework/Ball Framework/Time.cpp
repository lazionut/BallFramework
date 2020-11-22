#include "Time.h"

Time::TimeAux::TimeAux()
	: deltaTime{ 0.0 }, realTime{ 0.0 }, realDelta{ 0.0 }, timeSinceStart{ 0.0 },
	timeScale{ 1.0f }, unscaledDelta{ 0.0 }, scaledTimeSinceStart{ 0.0 }, gameTime{ 0.0 },
	now{ std::chrono::system_clock::now() },
	last{ std::chrono::system_clock::now() } {}

void Time::TimeAux::Reset_Time()
{
	realTime = 0.0;
	deltaTime = 0.0;
	realDelta = 0.0;
	gameTime = 0.0;
	unscaledDelta = 0.0;
	timeScale = 1.0f;
}

Time::TimeAux Time::aux;

void Time::Reset_Time()
{
	aux.Reset_Time();
}

void Time::Update_Time()
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

void Time::Update_Done()
{
	aux.deltaTime = 0.0;
	aux.unscaledDelta = 0.0;
}

double Time::Get_Real_Delta()
{
	return aux.realDelta;
}

double Time::Get_Time_Since_Startup()
{
	return aux.timeSinceStart;
}

double Time::Get_Delta_Time()
{
	return aux.deltaTime;
}

double Time::Get_Real_Time()
{
	return aux.realTime;
}

double Time::Get_Unscaled_Delta_Time()
{
	return aux.unscaledDelta;
}

double Time::Get_Scaled_Time_Since_Start()
{
	return aux.scaledTimeSinceStart;
}

float Time::Get_Time_Scale()
{
	return aux.timeScale;
}

void Time::Set_Time_Scale(float timeScale)
{
	if (timeScale >= 0.0f)
	{
		aux.timeScale = timeScale;
	}
}