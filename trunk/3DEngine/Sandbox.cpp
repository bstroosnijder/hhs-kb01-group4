#include "Sandbox.h"

namespace engine
{
	//---Private attribute---
	//---Public attrubute---
	//---Private methods---
	//---Public methods---

	/**
	 * Creates a Sandbox.
	 */
	Sandbox::Sandbox()
	{
		this->kernel = new Kernel();
	}

	/**
	 * Destructs the Sandbox
	 */
	Sandbox::~Sandbox()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void Sandbox::CleanUp()
	{
	}

	/**
	 * Pulses the kernel
	 */
	void Sandbox::HeartBeat()
	{
		this->kernel->HeartBeat();
	}

	/**
	 * Adds a stratergy to the stratergy collection within the logger. 
	 * A stratergy determines which output is given(text or console).
	 * Multiple stratergies are possible.
	 * @param		LogStrategy*		logStrat is the stratergy that is added to the collection
	 * @return		void
	 */
	void Sandbox::AddLogStrategy(LogStrategy* argPLogStrat)
	{
		this->kernel->GetLogger()->AddStrategy(argPLogStrat);
	}

	/**
	 * Deletes a stratergy to the stratergy collection within the logger.
	 * @param		LogStrategy*		logStrat is the stratergy that is removed to the collection
	 * @return		void
	 */
	void Sandbox::RemoveLogStrategy(LogStrategy* argPLogStrat)
	{
		//logger->RemoveStrategy(logStrat);
	}

	/**
	 * Creates a Window (does nothing more than that now)
	 * Window also needs a scene object. (not yet implemented)
	 * @param		int		argWidth is the width of the new window
	 * @param		int		argHeight is the height of the new window
	 * @return		void
	 */
	void Sandbox::NewWindow()
	{
		this->kernel->GetWindowManager()->NewWindow();
	}






	void Sandbox::CreateScene()
	{
		//not sure if neccesary
		//creates a scene needs to direct to scenemanager class.
	}

	/**
	 * Adds a scene to the scene collection within the Scene manager
	 * @param		Scene*		argScene is the scene that will be add in the collection
	 * @return		void
	 */
	void Sandbox::AddScene(Scene* argScene)
	{
		//sceneManager -> AddScene(argScene);
	}

	/**
	 * Removes a scene to the scene collection within the Scene manager
	 * @param		Scene*		argScene is the scene that will be removed in the collection
	 * @return		void
	 */
	void Sandbox::RemoveScene(Scene* argScene)
	{
		//sceneManager -> RemoveScene(argScene);
	}
}