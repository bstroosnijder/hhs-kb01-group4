#ifndef LOGGER_H_
#define LOGGER_H_
// to suppres the warning that we should use the windows specific "localtime_s" instead of just localtime
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <sstream>
#include <iostream>
#include <list>
#include <ctime>
#include "LogStrategy.h"

namespace engine
{
	/**
	 * The Logger class holds the strategies which define the output methods of the logger.
	 */
	class Logger
	{
	private:
		static std::list<LogStrategy*> strategies;
		static char* Logger::GetSeverity(int argSeverity);
	public:
		static const int INFO;
		static const int WARNING;
		static const int FATAL;

		static void AddStrategy(LogStrategy* argPStrat);
		static void RemoveStrategy(LogStrategy* argPStrat);
		static std::list<LogStrategy*> GetStrategies();
		static void Log(std::string argMessage, int argSeverity, char* argPFileName, int argLineNumber);
	};
}

#endif