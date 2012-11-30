#include "Kernel.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Construct the Kernel object.
	 */
	Kernel::Kernel()
	{
		renderers = std::vector<Renderer*>();
		Renderer* dx9renderer = new DirectX9Renderer();
		renderers.push_back(dx9renderer);
		
		windowManager = new WindowManager();
		sceneManager = new SceneManager();
		resourceManager = new ResourceManager();
		inputManager = new InputManager();

		LogStrategy* textStrat = new TextLog();
		LogStrategy* consoleStrat = new ConsoleLog();

		logger.AddStrategy(textStrat);
		logger.AddStrategy(consoleStrat);
	}

	/**
	 * Destruct the Kernel object.
	 * @return	void
	 */
	Kernel::~Kernel()
	{

	}

	/**
	 * Run the kernel.
	 * @return	void
	 */
	void Kernel::Run()
	{

	}

	/**
	 * Obtain the Logger object associated with the Kernel.
	 * @return	logger	Returns the logger associated with the kernel.
	 */
	Logger Kernel::GetLogger()
	{
		return this->logger;
	}
}