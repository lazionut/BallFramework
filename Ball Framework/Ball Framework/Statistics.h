#pragma once
#include "PlayersStatistics.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

namespace BallFramework
{

	class Statistics
	{
	public:
		Statistics();

	private:
		void MergeFiles();
		void ShowFinal();

	private:
		const std::vector<std::string> m_paths = { "..\\Assets\\statisticsPong.txt", "..\\Assets\\statisticsPongMP.txt",
			"..\\Assets\\statisticsBB.txt", "..\\Assets\\statisticsBBC.txt", "..\\Assets\\statisticsBBVS.txt" };
		const std::string m_finalPath = "..\\Assets\\statistics.txt";
		std::vector<PlayersStatistics> m_stats;
	};

}