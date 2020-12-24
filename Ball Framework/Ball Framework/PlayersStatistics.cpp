#include "PlayersStatistics.h"


PlayersStatistics::PlayersStatistics()
{
}

PlayersStatistics::PlayersStatistics(const std::string& filePath) : m_noPlayers{ 0 }, m_filePath{ filePath }
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
		int gamesPlayed;
		int gamesWon;
		int gamesLost;
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
				m_statistics.emplace(gamesWon - gamesLost, PlayerEntry{ playerName,gamesPlayed,gamesWon,gamesLost });

			}
		}
	}
	else
		std::cout << "File could not be opened ";
	fin.close();
}

void PlayersStatistics::UpdateStatistics(std::string playerName, bool isWon)
{
	if (playerName != "")
	{
		bool found = false;
		for (auto& player : m_statistics)
		{
			if (player.second.GetPlayerName() == playerName)
			{
				found = true;
				PlayerEntry temp{ playerName,player.second.GetGamesPlayed() + 1,player.second.GetGamesWon(),player.second.GetGamesLost() };
				if (isWon)
				{
					temp.SetGamesWon(player.second.GetGamesWon() + 1);
				}
				else
					temp.SetGamesLost(player.second.GetGamesLost() + 1);
				m_statistics.erase(player.first);
				m_statistics.emplace(temp.GetGamesWon() - temp.GetGamesLost(), temp);
				break;
			};
		}
		if (!found)
		{
			++m_noPlayers;
			PlayerEntry temp{ playerName,1,0,0 };
			if (isWon)
			{
				temp.SetGamesWon(temp.GetGamesWon() + 1);
			}
			else
				temp.SetGamesLost(temp.GetGamesLost() + 1);
			m_statistics.emplace(temp.GetGamesWon() - temp.GetGamesLost(), temp);
		}
	}

	std::ofstream fout(m_filePath);

	fout << m_noPlayers << std::endl;

	for (auto& player : m_statistics)
	{
		fout << player.second.GetPlayerName() << " ";
		fout << player.second.GetGamesPlayed() << " ";
		fout << player.second.GetGamesWon() << " ";
		fout << player.second.GetGamesLost() << std::endl;
	}
	fout.close();
}

std::ostream& operator<<(std::ostream& outStream, PlayersStatistics& other)
{

	for (auto& player : other.m_statistics)
	{

		outStream << player.second.GetPlayerName() << " ";
		outStream << player.second.GetGamesPlayed() << " ";
		outStream << player.second.GetGamesWon() << " ";
		outStream << player.second.GetGamesLost() << std::endl;
	}
	return outStream;
}