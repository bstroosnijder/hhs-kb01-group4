#include <iostream>
#include "Kernel.h"
#include "Logger.h"
#include "ConsoleLog.h"


int main()
{
	engine::Kernel kernel = engine::Kernel();
	engine::Logger log = engine::Logger();

	engine::LogStrategy* consStrat = new engine::ConsoleLog();

	log.AddStrategy(consStrat);
	log.Log("Pijn!", log.LOG_LEVEL_ERROR, __FILE__, __LINE__);

	system("pause");
	return 0;
}