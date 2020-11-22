#pragma once
#include <chrono>

class Time
{
private:
	class TimeAux
	{
	private:
		double deltaTime;
		double realDelta;
		double timeSinceStart;
		double realTime;
		double gameTime;
		double scaledTimeSinceStart;
		double unscaledDelta;
		float timeScale;

		std::chrono::time_point<std::chrono::system_clock> last;
		std::chrono::time_point<std::chrono::system_clock> now;

		TimeAux();

		void Reset_Time();

	public:
		TimeAux(const TimeAux&) = delete;
		TimeAux& operator=(const TimeAux&) = delete;

		friend class Time;
	};

	static TimeAux aux;

	Time();

	static void Reset_Time();
	static void Update_Time();
	static void Update_Done();

	//friend class Game;

public:
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;

	static double Get_Real_Delta();
	static double Get_Time_Since_Startup();
	static double Get_Delta_Time();
	static double Get_Real_Time();
	static double Get_Unscaled_Delta_Time();
	static double Get_Scaled_Time_Since_Start();
	static float Get_Time_Scale();
	static void Set_Time_Scale(float timeScale);
};