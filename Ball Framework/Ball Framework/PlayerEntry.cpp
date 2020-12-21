#include "PlayerEntry.h"

PlayerEntry::PlayerEntry()
{
}

PlayerEntry::PlayerEntry(std::string name, uint16_t gamesPlayed, uint16_t gamesWon, uint16_t gamesLost):
	m_playerName{ name }, m_gamesPlayed{ gamesPlayed }, m_gamesWon{ gamesWon }, m_gamesLost{gamesLost}
{
}

std::string PlayerEntry::GetPlayerName()
{
	return m_playerName;
}

uint16_t PlayerEntry::GetGamesPlayed() const
{
	return m_gamesPlayed;
}

uint16_t PlayerEntry::GetGamesWon() const
{
	return m_gamesWon;
}

uint16_t PlayerEntry::GetGamesLost() const
{
	return m_gamesLost;
}

void PlayerEntry::SetGamesPlayed(uint16_t gamesPlayed)
{
	m_gamesPlayed = gamesPlayed;
}

void PlayerEntry::SetGamesWon(uint16_t gamesWon)
{
	m_gamesWon = gamesWon;
}

void PlayerEntry::SetGamesLost(uint16_t gamesLost)
{
	m_gamesLost = gamesLost;
}


