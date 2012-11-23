#include "LogStrategy.h"
#include <fstream>
#include <iostream>

class TextLog : public LogStrategy
{
public:
	TextLog(void);
	~TextLog(void);

	void Write(char*, int severity);
};