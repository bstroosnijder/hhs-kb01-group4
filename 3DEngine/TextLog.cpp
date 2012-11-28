#include "TextLog.h"
#include <stdlib.h>

namespace engine
{
	TextLog::TextLog()
	{

	}

	TextLog::~TextLog()
	{

	}

	void TextLog::Write(char* argPMessage, char* argPSeverity, char* argPDate, char* argPTime, char* argPFileName, int argLineNumber)
	{
		//File gets created and opened. If the file exists the file will just be opened
		std::ofstream logFile("Logs//logTest.txt", std::ofstream::app);
		logFile << "[" << argPDate << "][" <<  argPTime << "][" << argPSeverity << 
			"]["<< argPMessage << "]["<< argPFileName << " on line " << argLineNumber <<"]" << std::endl;
		logFile.close();
	}
}