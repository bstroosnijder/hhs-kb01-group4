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
		std::list<LogStrategy*> strategies;

		char* Logger::GetSeverity(int argSeverity);
	public:
		static const int LOG_LEVEL_INFO;
		static const int LOG_LEVEL_WARNING;
		static const int LOG_LEVEL_ERROR;

		Logger();
		~Logger();
		void AddStrategy(LogStrategy* argPStrat);
		void RemoveStrategy(LogStrategy* argPStrat);
		std::list<LogStrategy*> GetStrategies();
		void Log(char* argPMessage, int argSeverity, char* argPFileName, int argLineNumber);
	};
}

#endif