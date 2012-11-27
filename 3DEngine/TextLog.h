#include "LogStrategy.h"
#include <fstream>
#include <iostream>

namespace engine
{
	class TextLog : public LogStrategy
	{
	public:
		TextLog(void);
		~TextLog(void);

		virtual void Write(char* argPMessage, char* argPSeverity, char* argPDate, char* argPTime, char* argPFileName, int argLineNumber);
	};
}