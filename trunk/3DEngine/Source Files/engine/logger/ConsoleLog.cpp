#include "..\..\..\Header Files\engine\logger\ConsoleLog.h"

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
	 * Destructs the ConsoleLog object.
	 * @return		void
	 */
	ConsoleLog::~ConsoleLog()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void ConsoleLog::CleanUp()
	{
	}

	/**
	 * Write a message to the console.
	 * @param		std::string	Char pointer that contains the message to be printed to the console.
	 * @param		char*		Char pointer that contains the textual representation of the severity of the log item.
	 * @param		char*		Char pointer that contains the date on which this message was emitted.
	 * @param		char*		Char pointer that contains the time on which this message was emitted.
	 * @param		char*		Char pointer that contains the file name in which this message was emitted.
	 * @param		int			Integer that indicates the line number on which this message was emitted.
	 * @return		void
	 */
	void ConsoleLog::Write(std::string argMessage, char* argPSeverity, char* argPDate, char* argPTime, char* argPFileName, int argLineNumber)
	{
		printf("[%s] [%s] %s\n", argPTime, argPSeverity, argMessage.c_str());
	}
}