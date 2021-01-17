#include "Statistics.h"
namespace BallFramework
{

	Statistics::Statistics()
	{
		for (auto&& path : m_paths) {
			m_stats.emplace_back(PlayersStatistics(path));
		}
		MergeFiles();
		ShowFinal();
	}

	void Statistics::MergeFiles()
	{
		std::ofstream out(m_finalPath);
		out << "---Games Statistics---" << std::endl;
		out << std::setiosflags(std::ios::fixed | std::ios::showpoint | std::ios::right) <<
			"Format: Player Name" << std::setw(10) <<
			"Games Played" << std::setw(10) <<
			"Games Won" << std::setw(10) <<
			"Games Lost" << std::setw(10) << std::endl << std::endl;
		uint8_t gameNum = 0;
		for (auto& stat : m_stats) {
			switch (gameNum) {
			case 0:
				out << "Pong Singleplayer" << std::endl;
				break;
			case 1:
				out << "Pong Multiplayer" << std::endl;
				break;
			case 2:
				out << "BrickBreaker Singleplayer" << std::endl;
				break;
			case 3:
				out << "BrickBreaker CO-OP" << std::endl;
				break;
			case 4:
				out << "BrickBreaker Versus" << std::endl;
				break;
			}
			out << stat << std::endl;
			++gameNum;
		}
		out.close();
	}

	void Statistics::ShowFinal()
	{
		system(m_finalPath.c_str());
	}

}