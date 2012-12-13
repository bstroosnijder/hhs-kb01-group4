#ifndef LOGGER_H_
#define LOGGER_H_

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
		

		static char* Logger::GetSeverity(int argSeverity);
	public:
		static std::list<LogStrategy*> strategies;
		static const int LOG_LEVEL_INFO;
		static const int LOG_LEVEL_WARNING;
		static const int LOG_LEVEL_ERROR;

		static void AddStrategy(LogStrategy* argPStrat);
		static void RemoveStrategy(LogStrategy* argPStrat);
		static std::list<LogStrategy*> GetStrategies();
		static void Log(char* argPMessage, int argSeverity, char* argPFileName, int argLineNumber);
	};
}

#endif