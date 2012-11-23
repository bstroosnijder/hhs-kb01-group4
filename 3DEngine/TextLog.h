#include "LogStrategy.h"

class TextLog : public LogStrategy
{
public:
	TextLog(void);
	~TextLog(void);

	void Write(char*, int severity);
};