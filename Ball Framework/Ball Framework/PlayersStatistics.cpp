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

void Swap(std::vector<std::variant<std::string, uint16_t>>* first, std::vector<std::variant<std::string, uint16_t>>* second)
{
	std::vector<std::variant<std::string, uint16_t>>* temp;
	temp = first;
	first = second;
	second = temp;

}
void OrderStatistiscs(std::vector<std::vector< std::variant <std::string, uint16_t> > >& statistics)
{

	for (uint16_t index = 0; index < statistics.size() - 1; index++)
	{
		for (uint16_t index2 = index; index2 < statistics.size(); index2++)
		{
			uint16_t firstScore = std::get<uint16_t>(statistics[index][2]) - std::get<uint16_t>(statistics[index][3]);
			uint16_t secondScore = std::get<uint16_t>(statistics[index2][2]) - std::get<uint16_t>(statistics[index2][3]);

			if (firstScore < secondScore)
			{
				Swap(&statistics[index], &statistics[index2]);
			}
		}
	}

}

std::ostream& operator<<(std::ostream& outStream, PlayersStatistics& other)
{


	OrderStatistiscs(other.m_statistics);

	for (uint16_t index = 0; index < other.m_noPlayers; index++)
	{
		outStream << std::get<std::string>(other.m_statistics[index][0]) << " ";
		outStream << std::get<std::uint16_t>(other.m_statistics[index][1]) << " ";
		outStream << std::get<std::uint16_t>(other.m_statistics[index][2]) << " ";
		outStream << std::get<std::uint16_t>(other.m_statistics[index][3]) << std::endl;
	}
	return outStream;
}