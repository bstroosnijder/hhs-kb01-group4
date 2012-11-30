#include "ConsoleLog.h"

namespace engine
{
	//---Private attributes---

	//---Public attributes---

	//---Private methods---

	//---Public methods---

	/**
	 * Construct the ConsoleLog object.
	 */
	ConsoleLog::ConsoleLog()
	{

	}

	/**
	 * Destruct the ConsoleLog object.
	 * @return	void
	 */
	ConsoleLog::~ConsoleLog()
	{

	}

	/**
	 * Write a message to the console.
	 * @param	argPMessage		Char pointer that contains the message to be printed to the console.
	 * @param	argPSeverity	Char pointer that contains the textual representation of the severity of the log item.
	 * @param	argPDate		Char pointer that contains the date on which this message was emitted.
	 * @param	argPTime		Char pointer that contains the time on which this message was emitted.
	 * @param	argPFileName	Char pointer that contains the file name in which this message was emitted.
	 * @param	argLineNumber	Integer that indicates the line number on which this message was emitted.
	 * @return	void
	 */
	void ConsoleLog::Write(char* argPMessage, char* argPSeverity, char* argPDate, char* argPTime, char* argPFileName, int argLineNumber)
	{
		printf("[%s] [%s] [%s] %s at %s on line %d\n\n", argPDate, argPTime, argPSeverity, argPMessage, argPFileName, argLineNumber);
	}
}