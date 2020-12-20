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
	fin >> m_noPlayers;
	if (fin.is_open())
	{
		std::vector< std::variant <std::string, uint16_t> > playerEntry;

		for (int i = 0; i < m_noPlayers; i++)
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
		std::cout << "File could not be opened ";
	fin.close();
}

void PlayersStatistics::UpdateStatistics(std::variant<std::string, uint16_t> playerName, const std::string& outFile, bool isWon)
{
	//playerName gamesPlayed gamesWon gamesLost
	bool found = false;
	for (auto& player : m_statistics)
	{
		if (player[0] == playerName)
		{
			found = true;
			std::variant<std::string, uint16_t> temp = std::get<uint16_t>(player[1]) + 1;
			player[1] = temp;

			if (isWon)
			{
				temp = std::get<uint16_t>(player[2]) + 1;
				player[2] = temp;
			}
			else
			{
				temp = std::get<uint16_t>(player[3]) + 1;
				player[3] = temp;
			}
		}
	}
	if (!found)
	{
		std::vector< std::variant <std::string, uint16_t> > playerEntry;
		std::variant<std::string, uint16_t> temp = playerName;
		playerEntry.push_back(temp);
		temp = 1;
		playerEntry.push_back(temp);
		if (isWon)
		{
			playerEntry.push_back(temp);
			temp = 0;
			playerEntry.push_back(temp);
		}
		else
		{
			temp = 0;
			playerEntry.push_back(temp);
			temp = 1;
			playerEntry.push_back(temp);
		}
		m_statistics.push_back(playerEntry);
		++m_noPlayers;
	}

	std::ofstream fout(outFile);
	fout << m_noPlayers << std::endl;
	for (auto& player : m_statistics)
	{
		fout << std::get<std::string>(player[0]) << " ";
		fout << std::get<std::uint16_t>(player[1]) << " ";
		fout << std::get<std::uint16_t>(player[2]) << " ";
		fout << std::get<std::uint16_t>(player[3]) << std::endl;
	}
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