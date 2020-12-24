#include "PlayerEntry.h"

PlayerEntry::PlayerEntry() : m_playerName{ "" }, m_gamesPlayed{ 0 }, m_gamesWon{ 0 }, m_gamesLost{ 0 }
{
}

PlayerEntry::PlayerEntry(std::string name) : m_playerName{ name }, m_gamesPlayed{ 0 }, m_gamesWon{ 0 }, m_gamesLost{ 0 }
{
}

PlayerEntry::PlayerEntry(std::string name, int gamesPlayed, int gamesWon, int gamesLost) :
	m_playerName{ name }, m_gamesPlayed{ gamesPlayed }, m_gamesWon{ gamesWon }, m_gamesLost{ gamesLost }
{
}

PlayerEntry::PlayerEntry(const PlayerEntry& other) noexcept
{
	*this = other;
}

PlayerEntry::PlayerEntry(PlayerEntry&& other) noexcept
{
	*this = std::move(other);
}

std::string PlayerEntry::GetPlayerName() const
{
	return m_playerName;
}

int PlayerEntry::GetGamesPlayed() const
{
	return m_gamesPlayed;
}

int PlayerEntry::GetGamesWon() const
{
	return m_gamesWon;
}

int PlayerEntry::GetGamesLost() const
{
	return m_gamesLost;
}

void PlayerEntry::SetGamesPlayed(int gamesPlayed)
{
	m_gamesPlayed = gamesPlayed;
}

void PlayerEntry::SetGamesWon(int gamesWon)
{
	m_gamesWon = gamesWon;
}

void PlayerEntry::SetGamesLost(int gamesLost)
{
	m_gamesLost = gamesLost;
}

PlayerEntry& PlayerEntry::operator=(const PlayerEntry& other)
{
	m_playerName = other.m_playerName;
	m_gamesPlayed = other.m_gamesPlayed;
	m_gamesWon = other.m_gamesWon;
	m_gamesLost = other.m_gamesLost;
	return *this;
}

PlayerEntry& PlayerEntry::operator=(PlayerEntry&& other) noexcept
{
	m_playerName = other.m_playerName;
	m_gamesPlayed = other.m_gamesPlayed;
	m_gamesWon = other.m_gamesWon;
	m_gamesLost = other.m_gamesLost;
	new(&other)PlayerEntry;
	return *this;
}

bool PlayerEntry::operator>(const PlayerEntry& other) const
{
	if (this->GetGamesWon() - this->GetGamesLost() > other.GetGamesWon() - other.GetGamesWon())
		return true;
	return false;
}

bool PlayerEntry::operator>=(const PlayerEntry& other) const
{
	if (this->GetGamesWon() - this->GetGamesLost() >= other.GetGamesWon() - other.GetGamesWon())
		return true;
	return false;
}

bool PlayerEntry::operator<(const PlayerEntry& other) const
{
	if (this->GetGamesWon() - this->GetGamesLost() < other.GetGamesWon() - other.GetGamesWon())
		return true;
	return false;
}

bool PlayerEntry::operator<=(const PlayerEntry& other) const
{
	if (this->GetGamesWon() - this->GetGamesLost() <= other.GetGamesWon() - other.GetGamesWon())
		return true;
	return false;
}

bool PlayerEntry::operator==(const PlayerEntry& other) const
{
	if (this->GetPlayerName() == other.GetPlayerName())
		return true;
	return false;
}
