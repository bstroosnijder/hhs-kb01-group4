#include "Sandbox.h"

namespace engine
{
	//---Private attribute---
	//---Public attrubute---
	//---Private methods---
	//---Public methods---

	/**
	 * Creates a Sandbox. And ilitialize the managers
	 * @return	Sandbox
	 */
	Sandbox::Sandbox()
	{
		windowManager = new WindowManager();
		logger = new Logger();
		sceneManager = new SceneManager();
	}

	/**
	 * Creates a Sandbox. And ilitialize the managers
	 * @return	Sandbox
	 */
	Sandbox::~Sandbox()
	{
		//destructor
	}

	/**
	 * Creates a Kernel. 
	 * @return	void
	 */
	void Sandbox::Start()
	{
		//maybe handig to do this within the constructor
		kernel = new Kernel();
	}

	/**
	 * Creates a Window (does nothing more than that now)
	 * Window also needs a scene object. (not yet implemented)
	 * @param	int			argWidth is the width of the new window
	 * @param	int			argHeight is the height of the new window
	 * @return	void
	 */
	void Sandbox::NewWindow(int argWidth, int argHeight)
	{
		windowManager -> NewWindow(argWidth, argHeight);
	}

	void Sandbox::CreateScene()
	{
		//not sure if neccesary
		//creates a scene needs to direct to scenemanager class.
	}

	/**
	 * Adds a scene to the scene collection within the Scene manager
	 * @param	Scene*		argScene is the scene that will be add in the collection
	 * @return	void
	 */
	void Sandbox::AddScene(engine::Scene* argScene)
	{
		sceneManager -> AddScene(argScene);
	}

	/**
	 * Removes a scene to the scene collection within the Scene manager
	 * @param	Scene*		argScene is the scene that will be removed in the collection
	 * @return	void
	 */
	void Sandbox::RemoveScene(engine::Scene* argScene)
	{
		sceneManager -> RemoveScene(argScene);
	}

	/**
	 * Adds a stratergy to the stratergy collection within the logger. 
	 * A stratergy determines which output is given(text or console).
	 * Multiple stratergies are possible.
	 * @param	LogStrategy*		logStrat is the stratergy that is added to the collection
	 * @return	void
	 */
	void Sandbox::AddLogStrategy(LogStrategy* logStrat)
	{
		logger->AddStrategy(logStrat);
	}

	/**
	 * Deletes a stratergy to the stratergy collection within the logger.
	 * @param	LogStrategy*		logStrat is the stratergy that is removed to the collection
	 * @return	void
	 */
	void Sandbox::RemoveLogStrategy(LogStrategy* logStrat)
	{
		logger->RemoveStrategy(logStrat);
	}
}