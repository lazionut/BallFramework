#include "PlayersStatistics.h"


PlayersStatistics::PlayersStatistics()
{
}

PlayersStatistics::PlayersStatistics(const std::string& filePath) : m_noPlayers{ 0 }, m_filePath{filePath}
{
	ReadStatistics(filePath);
}


void PlayersStatistics::ReadStatistics(const std::string& inFile)
{

	std::ifstream fin(inFile);
	
	if (fin.is_open())
	{
		PlayerEntry playerEntry;
		std::string playerName;
		uint16_t gamesPlayed;
		uint16_t gamesWon;
		uint16_t gamesLost;
		if (fin.peek() == std::ifstream::traits_type::eof())
		{
			m_noPlayers = 0;
		}
		else
		{
			fin >> m_noPlayers;
			for (auto index = 0; index < m_noPlayers; index++)
			{

				fin >> playerName;
				fin >> gamesPlayed;
				fin >> gamesWon;
				fin >> gamesLost;

				m_statistics.emplace(m_statistics.begin(), PlayerEntry{ playerName,gamesPlayed,gamesWon,gamesLost });
				
			}
			
			//if (m_statistics.empty()) m_noPlayers = 0;
		}
	}
	else
		std::cout << "File could not be opened ";
	fin.close();
}

void PlayersStatistics::UpdateStatistics(std::string playerName, bool isWon)
{
	//playerName gamesPlayed gamesWon gamesLost
	bool found = false;
	for (auto& player : m_statistics)
	{
		if (player.GetPlayerName() == playerName)
		{
			player.SetGamesPlayed(player.GetGamesPlayed() + 1);

			if (isWon)
				player.SetGamesWon(player.GetGamesWon() + 1);
			else
				player.SetGamesLost(player.GetGamesLost() + 1);
			found = true;
		}
	}
	if (!found && playerName!="")
	{
		if (isWon)
			m_statistics.emplace(m_statistics.end(),PlayerEntry{ playerName,1,1,0 });
		else
			m_statistics.emplace(m_statistics.end(), PlayerEntry{ playerName,1,0,1 });
		++m_noPlayers;
	}

	std::ofstream fout(m_filePath);

	fout << m_noPlayers<<std::endl;

	for (auto& player : m_statistics)
	{
		fout <<player.GetPlayerName() << " ";
		fout <<player.GetGamesPlayed()  << " ";
		fout <<player.GetGamesWon()  << " ";
		fout <<player.GetGamesLost()<< std::endl;
	}
	fout.close();
}

void Swap(PlayerEntry* first, PlayerEntry* second)
{
	PlayerEntry* temp;
	temp = first;
	first = second;
	second = temp;
}
void OrderStatistiscs(std::vector<PlayerEntry>& statistics)
{
	for (auto index1=0 ; index1 < statistics.size();index1++)
	{
		for (auto index2=0; index2 < statistics.size(); index2++)
		{
			auto firstScore = statistics[index1].GetGamesWon() - statistics[index1].GetGamesWon();
			auto secondScore = statistics[index2].GetGamesWon() - statistics[index2].GetGamesWon();

			if (firstScore < secondScore)
			{
				Swap(&statistics[index1], &statistics[index2]);
			}
		}
	}

}

std::ostream& operator<<(std::ostream& outStream, PlayersStatistics& other)
{
	OrderStatistiscs(other.m_statistics);

	for (uint16_t index = 0; index < other.m_noPlayers; index++)
	{ 
		outStream << other.m_statistics[index].GetPlayerName() <<" " << other.m_statistics[index].GetGamesPlayed()<< " " << other.m_statistics[index].GetGamesWon()<< " " << other.m_statistics[index].GetGamesLost();
	}
	return outStream;
}