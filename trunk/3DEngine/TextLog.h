#ifndef TEXTLOG_H_
#define TEXTLOG_H_

#include "LogStrategy.h"
#include <fstream>

namespace engine
{
	/**
	 * The TextLog class is responsible for printing log messages to a logfile.
	 */
	class TextLog : public LogStrategy
	{
	public:
		TextLog();
		~TextLog();
		virtual void Write(char* argPMessage, char* argPSeverity, char* argPDate, char* argPTime, char* argPFileName, int argLineNumber);
	};
}

#endif