#include "TextLog.h"

TextLog::TextLog(void)
{

}

TextLog::~TextLog(void)
{

}

void TextLog::Write(char* argMessage, int severity)
{
	
	std::ofstream logFile;	
	//ate is used of at end and in is used for input
	logFile.open("Logs//logTest.txt", std::ofstream::in | std::ofstream::ate);
	logFile << argMessage << std::endl;
	logFile.close();
}