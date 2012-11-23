#include <iostream>
#include "ConsoleLog.h"

ConsoleLog::ConsoleLog(void)
{

}

ConsoleLog::~ConsoleLog(void)
{

}

void ConsoleLog::Write(char* message, int severity)
{
	printf("%s %d\n", message, severity);


	//std::cout << *message << " " << severity;
}