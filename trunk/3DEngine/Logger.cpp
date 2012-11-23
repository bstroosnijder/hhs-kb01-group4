#include "Logger.h";

const int Logger::LOG_LEVEL_INFO = 1;
const int Logger::LOG_LEVEL_WARNING = 2;
const int Logger::LOG_LEVEL_ERROR = 3;

Logger::Logger()
{
	
}

void Logger::AddStrategy(LogStrategy* strategy) 
{
	this->strategies.push_back(strategy);
}

void Logger::RemoveStrategy(LogStrategy* strategy)
{
	this->strategies.remove(strategy);
}

std::list<LogStrategy*> Logger::GetStrategies()
{
	return this->strategies;
}

void Logger::Log(char* message, int severity)
{
	//Get current datetime.
	time_t now = time(0);
	tm *ltm = localtime(&now);

	//Extract the date out of the datetime.
	char* year = (char*)(1900 + ltm->tm_year);


	/*time.now();
	datum
	tijd
	file name line number*/

	for each(LogStrategy* strat in this->strategies)
	{
		strat->Write(message, severity);
	}
}