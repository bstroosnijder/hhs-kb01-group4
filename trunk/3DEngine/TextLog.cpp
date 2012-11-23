#include "TextLog.h"
#include <stdlib.h>

TextLog::TextLog(void)
{

}

TextLog::~TextLog(void)
{

}

void TextLog::Write(char* argPMessage, char* argPSeverity, char* argPDate, char* argPTime, char* argPFileName, int argLineNumber)
{
	//std::ofstream logFile;
	std::ofstream logFile("Logs//logTest.txt", std::ofstream::app);
	//logFile.fopen("Logs//logTest.txt", std::ofstream::in | std::ofstream::ate );
	//char* pBuffer = "";
	//sprintf( pBuffer, "[%s] [%s] [%s] %s at %s on line %d\n\n", argPDate, argPTime, argSeverity, argPMessage, argPFileName, argLineNumber);
	//logFile << *pBuffer;
	logFile << "[" << argPDate << "][" <<  argPTime << "][" << argPSeverity << 
		"]["<< argPMessage << "]["<< argPFileName << " on line " << argLineNumber <<"]" << std::endl;
	logFile.close();
}