#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "PlayerEntry.h"

class PlayersStatistics
{
public:
	PlayersStatistics();
	PlayersStatistics(const std::string& filePath);
	void ReadStatistics(const std::string& inFile);
	void UpdateStatistics(std::string playerName, bool isWon);

	friend void Swap( PlayerEntry * first, PlayerEntry* second);
	friend void OrderStatistiscs(std::vector<PlayerEntry>& statistics); //TO DO: optimise

	friend std::ostream& operator<<(std::ostream& outStream, PlayersStatistics& other);
private:

	std::vector<PlayerEntry> m_statistics;
	std::string m_filePath;
	uint16_t m_noPlayers;
};

