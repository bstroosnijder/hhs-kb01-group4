#include "Kernel.h"

namespace engine
{
	Kernel::Kernel(void)
	{
		logger = Logger();

		WindowManager* windowManager = new WindowManager();
		SceneManager* sceneManager = new SceneManager();

		LogStrategy* textStrat = new TextLog();
		LogStrategy* consoleStrat = new ConsoleLog();

		logger.AddStrategy(textStrat);
		logger.AddStrategy(consoleStrat);
	}

	Kernel::~Kernel(void)
	{

	}

	Logger Kernel::GetLogger()
	{
		return this->logger;
	}
}