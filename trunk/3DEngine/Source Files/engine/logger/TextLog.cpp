#include "..\..\..\Header Files\engine\logger\TextLog.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Constructs the TextLog object.
	 */
	TextLog::TextLog()
	{
	}

	/**
	 * Destructs the TextLog object.
	 * @return		void
	 */
	TextLog::~TextLog()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void TextLog::CleanUp()
	{
	}

	/**
	 * Write a message to a text file.
	 * @param		char*		Char pointer that contains the message to be printed to the console.
	 * @param		char*		Char pointer that contains the textual representation of the severity of the log item.
	 * @param		char*		Char pointer that contains the date on which this message was emitted.
	 * @param		char*		Char pointer that contains the time on which this message was emitted.
	 * @param		char*		Char pointer that contains the file name in which this message was emitted.
	 * @param		int			Integer that indicates the line number on which this message was emitted.
	 * @return		void
	 */
	void TextLog::Write(std::string argPMessage, char* argPSeverity, char* argPDate, char* argPTime, char* argPFileName, int argLineNumber)
	{
		//File gets created and opened. If the file exists the file will just be opened.
		std::ofstream logFile("Logs//logTest.txt", std::ofstream::app);
		logFile << "[" << argPDate << "][" <<  argPTime << "][" << argPSeverity << 
			"]["<< argPMessage << "]["<< argPFileName << " on line " << argLineNumber <<"]" << std::endl;
		logFile.close();
	}
}