#ifndef LOGSTRATEGY_H_
#define LOGSTRATEGY_H_

namespace engine
{
	class LogStrategy
	{
	public:
		LogStrategy();
		virtual ~LogStrategy();

		virtual void Write(char* argPMessage, char* argPSeverity, char* argPDate, char* argPTime, char* argPFileName, int argLineNumber)=0;
	};
}

#endif