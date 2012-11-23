#ifndef LOGSTRATEGY_H_
#define LOGSTRATEGY_H_

class LogStrategy
{
public:
	LogStrategy();
	virtual ~LogStrategy();

	virtual void Write(char*, int severity)=0;
};

#endif