#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <list>
#include <ctime>
#include "LogStrategy.h"

namespace engine
{
	class Logger
	{
	private:
		//---Private attributes---
		std::list<LogStrategy*> strategies;

		//---Private methods---
		char* Logger::GetSeverity(int argSeverity);
	public:
		//---Public attributes---
		static const int LOG_LEVEL_INFO;
		static const int LOG_LEVEL_WARNING;
		static const int LOG_LEVEL_ERROR;

		//---Public methods---
		Logger();
		~Logger();
		void AddStrategy(LogStrategy* strat);
		void RemoveStrategy(LogStrategy* strat);
		std::list<LogStrategy*> GetStrategies();
		void Log(char* argPMessage, int argSeverity, char* argPFileName, int argLineNumber);
	};
}

#endif