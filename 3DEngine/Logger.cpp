#include "Logger.h";

namespace engine
{
	//---Private attributes---
	//---Public attributes---

	//One-time initialisation of the logger's constant variables.
	const int Logger::LOG_LEVEL_INFO = 1;
	const int Logger::LOG_LEVEL_WARNING = 2;
	const int Logger::LOG_LEVEL_ERROR = 3;

	//---Private methods---

	/**
	 * Obtain a string representation of the severity of the log item.
	 * @param	argSeverity		The integer representing the severity of the log item which should countain either 1, 2 or 3.
	 * @return					The string (char pointer) representing the severity of the log item.
	 */
	char* Logger::GetSeverity(int argSeverity)
	{
		char* severity;

		//Switch on argSeverity, checking if the number given matches any of the defined constants.
		//If it doesn't, 'UNKNOWN SEVERITY' is returned.
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

	//---Public methods---

	/**
	 * Construct the Logger object.
	 */
	Logger::Logger()
	{
		//Nothing here?
	}

	/**
	 * Destruct the Logger object.
	 * @return	void
	 */
	Logger::~Logger()
	{
		//Todo
	}

	/**
	 * Add a strategy to which the logger will log. 
	 * @param	argPStrategy	The LogStrategy to add to the logger.
	 * @return	void
	 */
	void Logger::AddStrategy(LogStrategy* argPStrategy) 
	{
		strategies.push_back(argPStrategy);
	}

	/**
	 * Remove a strategy from the logger to prevent the logger from logging to this strategy. 
	 * @param	argPStrategy	The LogStrategy to be removed from the logger.
	 * @return	void
	 */
	void Logger::RemoveStrategy(LogStrategy* argPStrategy)
	{
		strategies.remove(argPStrategy);
	}

	/**
	 * Obtain all the strategies the logger is currently logging to.
	 * @return					A list containing LogStrategy items which the logger is currently logging to.
	 */
	std::list<LogStrategy*> Logger::GetStrategies()
	{
		return strategies;
	}

	/**
	 * Log to all the strategies the logger contains.
	 * @param	argPMessage		The message that's going to be logged.
	 * @param	argSeverity		The severity of the strategy which should countain either 1, 2 or 3.
	 * @param	argPFile		The file from which the log action was called.
	 * @param	argLineNumber	The line number from which the log action was called.
	 * @return	void
	 */
	void Logger::Log(char* argPMessage, int argSeverity, char* argPFile, int argLineNumber)
	{	
		//Obtain a descriptive string version of the given severity number.
		char* severity = GetSeverity(argSeverity);

		//Log the message, severity (info/warning/error), current date, current time, file location and line number to each strategy.
		for each(LogStrategy* strat in strategies)
		{
			strat->Write(argPMessage, severity, __DATE__, __TIME__, argPFile, argLineNumber);
		}
	}
}