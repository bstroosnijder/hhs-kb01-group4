#include <iostream>
#include "ConsoleLog.h"

ConsoleLog::ConsoleLog(void)
{

}

ConsoleLog::~ConsoleLog(void)
{

}

void ConsoleLog::Write(char* argPMessage, char* argPSeverity, char* argPDate, char* argPTime, char* argPFileName, int argLineNumber)
{
	printf("[%s] [%s] [%s] %s at %s on line %d\n\n", argPDate, argPTime, argPSeverity, argPMessage, argPFileName, argLineNumber);
}