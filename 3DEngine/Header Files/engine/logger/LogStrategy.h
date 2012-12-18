#ifndef LOGSTRATEGY_H_
#define LOGSTRATEGY_H_

#include <string>

namespace engine
{
	/**
	 * The LogStrategy class defines an interface which must be implemented by its child classes. 
	 * This interface is using the Strategy Design Pattern. This lets us change the log output during runtime.
	 */
	class LogStrategy
	{
	public:
		virtual void Write(std::string argPMessage, char* argPSeverity, char* argPDate, char* argPTime, char* argPFileName, int argLineNumber)=0;
	};
}

#endif