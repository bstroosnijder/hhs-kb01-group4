#ifndef TEXTLOG_H_
#define TEXTLOG_H_

#include <fstream>
#include "LogStrategy.h"

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
		void CleanUp();
		virtual void Write(std::string argPMessage, char* argPSeverity, char* argPDate, char* argPTime, char* argPFileName, int argLineNumber);
	};
}

#endif