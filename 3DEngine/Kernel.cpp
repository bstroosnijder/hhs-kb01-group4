#include "Kernel.h"

namespace engine
{
	Kernel::Kernel(void)
	{
		windowManager = new WindowManager();
		sceneManager = new SceneManager();
		resourceManager = new ResourceManager();
		inputManager = new InputManager();

		LogStrategy* textStrat = new TextLog();
		LogStrategy* consoleStrat = new ConsoleLog();

		logger.AddStrategy(textStrat);
		logger.AddStrategy(consoleStrat);
	}

	Kernel::~Kernel(void)
	{
	}

	void Kernel::Run(void)
	{
	}

	Logger Kernel::GetLogger()
	{
		return this->logger;
	}
}