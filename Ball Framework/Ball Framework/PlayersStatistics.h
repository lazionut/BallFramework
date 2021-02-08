#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "PlayerEntry.h"
#include "../LoggerDLL/Logger.h"

namespace BallFramework
{

	class PlayersStatistics
	{
	public:
		PlayersStatistics() = default;
		PlayersStatistics(const std::string& filePath);
		void ReadStatistics(const std::string& inFile);
		void UpdateStatistics(std::string playerName, bool isWon);

		friend std::ostream& operator<<(std::ostream& outStream, PlayersStatistics& other);

		struct classcomp {
			bool operator() (const int left, const int right) const
			{
				return left > right;
			}
		};

	private:
		std::multimap<int, PlayerEntry, classcomp>m_statistics;
		std::string m_filePath;
		int m_noPlayers;
	};

}