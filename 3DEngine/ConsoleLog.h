#include "LogStrategy.h"

class ConsoleLog : public LogStrategy
{
public:
	ConsoleLog(void);
	~ConsoleLog(void);

	virtual void Write(char* argPMessage, char* argPSeverity, char* argPDate, char* argPTime, char* argPFileName, int argLineNumber);
};