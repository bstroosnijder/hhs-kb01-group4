#include <stdlib.h>
#include <iostream>
#include "Logger.h"
#include "ConsoleLog.h"

static Logger logger;

int main()
{
	LogStrategy* strat = new ConsoleLog();

	logger.AddStrategy(strat);
	logger.Write("FATAL SEVERE ERROR AU AU AU", Logger::LOG_LEVEL_ERROR);
	logger.Write("Hier, heb informatie", Logger::LOG_LEVEL_INFO);

	system("pause");

	return 0;
}