#include <stdlib.h>
#include <iostream>
#include "Logger.h"
#include "ConsoleLog.h"
#include "TextLog.h"

static Logger logger;

int main()
{
	LogStrategy* strat = new ConsoleLog();
	LogStrategy* strat2 = new TextLog();

	logger.AddStrategy(strat);
	logger.AddStrategy(strat2);
	logger.Log("FATAL SEVERE ERROR AU AU AU", Logger::LOG_LEVEL_ERROR, __FILE__, __LINE__);
	logger.Log("Hier, heb informatie", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
	logger.Log("Hier, heb meer informatie", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
	logger.Log("Hier, heb nog wat informatie", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
	logger.Log("Uhoh.. warning!", Logger::LOG_LEVEL_WARNING, __FILE__, __LINE__);
	logger.Log("ERROR!!", Logger::LOG_LEVEL_WARNING, __FILE__, __LINE__);

	system("pause");

	return 0;
}