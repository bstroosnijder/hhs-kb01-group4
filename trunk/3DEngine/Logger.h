#include <iostream>
#include <list>
#include <ctime>
#include "LogStrategy.h"

class Logger
{
private:
	//Private attributes.
	std::list<LogStrategy*> strategies;

	//Private methods.
	char* Logger::GetSeverity(int argSeverity);
public:
	//Constructors.
	Logger();
	
	//Public attributes.
	static const int LOG_LEVEL_INFO;
	static const int LOG_LEVEL_WARNING;
	static const int LOG_LEVEL_ERROR;

	//Public methods.
	void AddStrategy(LogStrategy* strat);
	void RemoveStrategy(LogStrategy* strat);
	std::list<LogStrategy*> GetStrategies();
	void Log(char* argPMessage, int argSeverity, char* argPFileName, int argLineNumber);
};