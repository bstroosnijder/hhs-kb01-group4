#include "TextLog.h"
#include <stdlib.h>

namespace engine
{
	/**
	 *	Constructor for TextLog class.
	*/
	TextLog::TextLog()
	{

	}

	/**
	 *	Destructor for TextLog class.
	 *	@return void
	*/
	TextLog::~TextLog()
	{

	}

	/**
	 *	The write method prints text to the logfile.
	 *	@param argPMessage		The message to be printed.
	 *	@param argPSeverity		Specifies the severity.
	 *	@param argPDate			The date to be printed.
	 *	@param argPTime			The time to be printed.
	 *	@param argPFileName		The file where this method is called. Use __FILE__.
	 *	@param argLineNumber	Line number where this method is called. Use __LINE__.
	*/
	void TextLog::Write(char* argPMessage, char* argPSeverity, char* argPDate, char* argPTime, char* argPFileName, int argLineNumber)
	{
		//File gets created and opened. If the file exists the file will just be opened
		std::ofstream logFile("Logs//logTest.txt", std::ofstream::app);
		logFile << "[" << argPDate << "][" <<  argPTime << "][" << argPSeverity << 
			"]["<< argPMessage << "]["<< argPFileName << " on line " << argLineNumber <<"]" << std::endl;
		logFile.close();
	}
}