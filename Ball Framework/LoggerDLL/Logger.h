#pragma once
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#ifdef LOGGERDLL_EXPORTS
#define LOGGING_API __declspec(dllexport)
#else
# define LOGGING_API __declspec(dllimport)
#endif

class LOGGING_API Logger
{
public:
	static void Initialize();

	static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }

private:
	static std::shared_ptr<spdlog::logger> s_Logger;
};

#define TRACE(...)  Logger::GetLogger()->trace(__VA_ARGS__)
#define INFO(...)   Logger::GetLogger()->info(__VA_ARGS__)
#define WARN(...)   Logger::GetLogger()->warn(__VA_ARGS__)
#define ERROR(...)  Logger::GetLogger()->error(__VA_ARGS__)
#define FATAL(...)  Logger::GetLogger()->fatal(__VA_ARGS__)