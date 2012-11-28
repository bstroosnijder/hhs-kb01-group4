#ifndef CONSOLELOG_H_
#define CONSOLELOG_H_
#include "LogStrategy.h"

namespace engine
{
	class ConsoleLog : public LogStrategy
	{
	public:
		ConsoleLog();
		~ConsoleLog();

		virtual void Write(char* argPMessage, char* argPSeverity, char* argPDate, char* argPTime, char* argPFileName, int argLineNumber);
	};
}

#endif