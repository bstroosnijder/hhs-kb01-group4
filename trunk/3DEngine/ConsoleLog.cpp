#include <iostream>
#include "ConsoleLog.h"

ConsoleLog::ConsoleLog(void)
{

}

ConsoleLog::~ConsoleLog(void)
{

}

void ConsoleLog::Write(char* argPMessage, int argSeverity, char* argPDate, char* argPTime, char* argPFileName, int argLineNumber)
{
	printf("%s %d\n", argPMessage, argSeverity);


	//std::cout << *message << " " << severity;
}