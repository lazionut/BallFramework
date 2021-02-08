#pragma once

#include<string>

namespace BallFramework
{

	class PlayerEntry
	{
	public:
		PlayerEntry();
		PlayerEntry(std::string name);
		PlayerEntry(std::string name, int gamesPlayed, int gamesWon, int gamesLost);
		PlayerEntry(const PlayerEntry& other) noexcept;
		PlayerEntry(PlayerEntry&& other) noexcept;

		std::string GetPlayerName() const;
		int GetGamesPlayed() const;
		int GetGamesWon() const;
		int GetGamesLost() const;

		void SetGamesPlayed(int gamesPlayed);
		void SetGamesWon(int gamesWon);
		void SetGamesLost(int gamesLost);

		PlayerEntry& operator= (const PlayerEntry& other);
		PlayerEntry& operator= (PlayerEntry&& other) noexcept;

		bool operator>(const PlayerEntry& other) const;
		bool operator>=(const PlayerEntry& other) const;
		bool operator<(const PlayerEntry& other) const;
		bool operator<=(const PlayerEntry& other) const;
		bool operator==(const PlayerEntry& other) const;

	private:
		std::string m_playerName;
		int m_gamesPlayed, m_gamesWon, m_gamesLost;
	};

}