#include <iostream>
#include <list>
#include <ctime>
#include "LogStrategy.h"

class Logger
{
private:
	std::list<LogStrategy*> strategies;

public:
	Logger();
	
	void AddStrategy(LogStrategy*);
	void RemoveStrategy(LogStrategy*);
	std::list<LogStrategy*> GetStrategies();

	void Log(char*, int);

	static const int LOG_LEVEL_INFO;
	static const int LOG_LEVEL_WARNING;
	static const int LOG_LEVEL_ERROR;
};