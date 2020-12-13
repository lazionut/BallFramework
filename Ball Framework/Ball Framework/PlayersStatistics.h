#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#include <variant>

class PlayersStatistics
{
public:
	PlayersStatistics();
	PlayersStatistics(uint16_t noPlayers);
	void ReadStatistics(const std::string& inFile);


	friend void Swap(std::vector < std::variant <std::string, uint16_t> >* first, std::vector < std::variant <std::string, uint16_t> >* second);
	friend void OrderStatistiscs(std::vector<std::vector< std::variant <std::string, uint16_t> > >& statistics);

	friend std::ostream& operator<<(std::ostream& outStream, PlayersStatistics& other);
private:

	std::vector<std::vector< std::variant <std::string, uint16_t> > > m_statistics;
	uint16_t m_noPlayers;
};

