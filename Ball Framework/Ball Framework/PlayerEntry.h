#pragma once
#include<string>

class PlayerEntry
{
public:
	PlayerEntry();
	PlayerEntry(std::string name, uint16_t gamesPlayed, uint16_t gamesWon, uint16_t gamesLost);

	std::string GetPlayerName();
	uint16_t GetGamesPlayed() const;
	uint16_t GetGamesWon() const;
	uint16_t GetGamesLost() const;

	void SetGamesPlayed(uint16_t gamesPlayed);
	void SetGamesWon(uint16_t gamesWon);
	void SetGamesLost(uint16_t gamesLost);

private: 
	std::string m_playerName;
	uint16_t m_gamesPlayed, m_gamesWon, m_gamesLost;
	//TO DO : highscore;
 };

