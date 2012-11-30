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
		//Renderer* dx9renderer = new DirectX9Renderer();
		//renderers.push_back(dx9renderer);
		
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
	/**
	 * The heartbeat makes sure that the windows will be rendered. 
	 * It also check of there is a window created. If it does it renders. If it does not nothing happens.
	 * Yeah this is dog. Sorry for the mess ;'(
	 * @return	void
	 */
	void Kernel::Heartbeat(int argRendererIndex){
		//an infenate loop to detemine if there is a window open. 
		//windowManager.method
		//ToDo
		//Renderer* renderer = renderers.at(argRendererIndex);
		//Renderer.
		//.Render
	}
}