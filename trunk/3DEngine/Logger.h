#include <iostream>
#include <list>
#include <ctime>
#include "LogStrategy.h"

class Logger
{
private:
	std::list<LogStrategy*> strategies;

	char* Logger::GetSeverity(int argSeverity);
public:
	Logger();
	
	void AddStrategy(LogStrategy* strat);
	void RemoveStrategy(LogStrategy* strat);
	std::list<LogStrategy*> GetStrategies();
	void Log(char* argPMessage, int argSeverity, char* argPFileName, int argLineNumber);

	static const int LOG_LEVEL_INFO;
	static const int LOG_LEVEL_WARNING;
	static const int LOG_LEVEL_ERROR;
};