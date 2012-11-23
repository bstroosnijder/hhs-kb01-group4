#include "LogStrategy.h"
#include <fstream>
#include <iostream>

class TextLog : public LogStrategy
{
public:
	TextLog(void);
	~TextLog(void);

	virtual void Write(char* argPMessage, int argSeverity, char* argPDate, char* argPTime, char* argPFileName, int argLineNumber);
};