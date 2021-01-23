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
		out << "Format:  Player Name " << 
			" Games Played " << 
			" Games Won " << 
			" Games Lost " <<  std::endl << std::endl;
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