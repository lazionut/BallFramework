#pragma once
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace myLogger
{

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
		Logger() = default;

		static std::shared_ptr<spdlog::logger> s_Logger;
	};

}

#define LOGGING_TRACE(...)  myLogger::Logger::GetLogger()->trace(__VA_ARGS__)
#define LOGGING_INFO(...)   myLogger::Logger::GetLogger()->info(__VA_ARGS__)
#define LOGGING_WARN(...)   myLogger::Logger::GetLogger()->warn(__VA_ARGS__)
#define LOGGING_ERROR(...)  myLogger::Logger::GetLogger()->error(__VA_ARGS__)