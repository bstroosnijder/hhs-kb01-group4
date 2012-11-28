#include <iostream>
#include "ConsoleLog.h"

namespace engine
{
	/**
	 *	Constructor for ConsoleLog class.
	*/
	ConsoleLog::ConsoleLog()
	{

	}

	/**
	 *	Destructor for ConsoleLog class.
	 *	@return void
	*/
	ConsoleLog::~ConsoleLog()
	{

	}

	/**
	 *	The write method prints text to the console output.
	 *	@param argPMessage		The message to be printed.
	 *	@param argPSeverity		Specifies the severity.
	 *	@param argPDate			The date to be printed.
	 *	@param argPTime			The time to be printed.
	 *	@param argPFileName		The file where this method is called. Use __FILE__.
	 *	@param argLineNumber	Line number where this method is called. Use __LINE__.
	*/
	void ConsoleLog::Write(char* argPMessage, char* argPSeverity, char* argPDate, char* argPTime, char* argPFileName, int argLineNumber)
	{
		printf("[%s] [%s] [%s] %s at %s on line %d\n\n", argPDate, argPTime, argPSeverity, argPMessage, argPFileName, argLineNumber);
	}
}