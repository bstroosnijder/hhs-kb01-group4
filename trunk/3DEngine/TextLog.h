#include "LogStrategy.h"
#include <fstream>
#include <iostream>

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