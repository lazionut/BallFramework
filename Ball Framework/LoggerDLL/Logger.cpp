#include "Logger.h"

namespace BallFramework
{

	std::shared_ptr<spdlog::logger> Logger::s_Logger;

	void Logger::Initialize()
	{
		spdlog::set_pattern("%^[%T]%n:%v%$");
		s_Logger = spdlog::stdout_color_mt("Logger");
		s_Logger->set_level(spdlog::level::trace);
	}

}