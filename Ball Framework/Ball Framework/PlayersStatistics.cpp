#include "PlayersStatistics.h"



PlayersStatistics::PlayersStatistics() : m_noPlayers{ 0 }
{
}

PlayersStatistics::PlayersStatistics(uint16_t noPlayers) : m_noPlayers{ noPlayers }
{
}

void PlayersStatistics::ReadStatistics(const std::string& inFile)
{
	std::string playerName;
	uint16_t gamesPlayed;
	uint16_t gamesWon;
	uint16_t gamesLost;
	uint16_t maxScore = 0;

	std::ifstream fin(inFile);

	if (fin.is_open())
	{
		std::vector< std::variant <std::string, uint16_t> > playerEntry;

		while (!fin.eof())
		{
			fin >> playerName;
			fin >> gamesPlayed;
			fin >> gamesWon;
			fin >> gamesLost;

			std::variant <std::string, uint16_t> nameMatchVariant;
			nameMatchVariant = playerName;
			playerEntry.emplace(playerEntry.end(), nameMatchVariant);

			nameMatchVariant = gamesPlayed;
			playerEntry.emplace(playerEntry.end(), nameMatchVariant);

			nameMatchVariant = gamesWon;
			playerEntry.emplace(playerEntry.end(), nameMatchVariant);

			nameMatchVariant = gamesLost;
			playerEntry.emplace(playerEntry.end(), nameMatchVariant);

			m_statistics.emplace(m_statistics.end(), playerEntry);

		}

	}
	else
		throw "File could not be opened ";
	fin.close();
}