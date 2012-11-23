#include "LogStrategy.h"

class ConsoleLog : public LogStrategy
{
public:
	ConsoleLog(void);
	~ConsoleLog(void);

	void Write(char*, int severity);
};