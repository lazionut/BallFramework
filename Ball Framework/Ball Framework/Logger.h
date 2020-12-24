#pragma once
#include <memory>
//#include "spdlog/spdlog.h" //nu gaseste biblioteca

class Logger
{
public:
	static void Initialize();

	//inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }

private:
	//static std::shared_ptr<stdlog::logger> s_Logger;
};