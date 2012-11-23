#include "Logger.h";

const int Logger::LOG_LEVEL_INFO = 1;
const int Logger::LOG_LEVEL_WARNING = 2;
const int Logger::LOG_LEVEL_ERROR = 3;

Logger::Logger()
{
	
}

void Logger::AddStrategy(LogStrategy* argPStrategy) 
{
	this->strategies.push_back(argPStrategy);
}

void Logger::RemoveStrategy(LogStrategy* argPStrategy)
{
	this->strategies.remove(argPStrategy);
}

std::list<LogStrategy*> Logger::GetStrategies()
{
	return this->strategies;
}

void Logger::Log(char* argPMessage, int argSeverity, char* argPFile, int argFileNumber)
{	
	char* severity = GetSeverity(argSeverity);

	for each(LogStrategy* strat in this->strategies)
	{
		strat->Write(argPMessage, argSeverity, __DATE__, __TIME__, argPFile, argFileNumber);
	}
}

//Private methods
char* Logger::GetSeverity(int argSeverity)
{
	char* severity;

	switch(argSeverity)
	{
	case LOG_LEVEL_INFO:
		severity = "INFO";
		break;
	case LOG_LEVEL_WARNING:
		severity = "WARNING";
		break;
	case LOG_LEVEL_ERROR:
		severity = "ERROR";
		break;
	default:
		severity = "UNKNOWN SEVERITY";
		break;
	}
	
	return severity;
}