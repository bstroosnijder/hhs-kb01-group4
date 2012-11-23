#include "TextLog.h"

TextLog::TextLog(void)
{

}

TextLog::~TextLog(void)
{

}

void TextLog::Write(char* argPMessage, char* argSeverity, char* argPDate, char* argPTime, char* argPFileName, int argLineNumber)
{
	std::ofstream logFile;	
	//ate is used of at end and in is used for input
	logFile.open("Logs//logTest.txt", std::ofstream::in | std::ofstream::ate);
	logFile << argPMessage << std::endl;
	logFile.close();
}