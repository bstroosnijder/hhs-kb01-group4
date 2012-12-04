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
	 * @return		void
	 */
	void Sandbox::HeartBeat()
	{
		this->kernel->HeartBeat();
	}

	/**
	 * Adds a stratergy to the stratergy collection within the logger. 
	 * A strategy determines which output is given(text or console).
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
	 * Creates a Window and creates the association with this Window and the Renderer object.
	 * @param		int		argRendererIndex is the index of the renderer to be added to the window we're creating.
	 * @return		Window*	returns the created window.
	 */
	Window* Sandbox::NewWindow(int argRendererIndex)
	{
		Renderer* pRenderer = this->kernel->GetRenderer(argRendererIndex);

		if(pRenderer == 0) 
		{
			std::stringstream msg;
			msg << "Renderer with index " << argRendererIndex << " could not be found!"; 
			this->kernel->GetLogger()->Log((char*)msg.str().c_str(), Logger::LOG_LEVEL_ERROR, __FILE__, __LINE__);
		}

		Window* pWindow = this->kernel->GetWindowManager()->NewWindow();
		this->kernel->AddWindowRenderer(pWindow, pRenderer);

		return pWindow;
	}

	/**
	 * Creates a Window and creates the association with this Window and the Renderer object.
	 * @param		int		argRendererIndex is the index of the renderer to be added to the window we're creating.
	 * @param		char*	argPTitle is the title for the new window
	 * @param		int		argX is the x-axis position for the new window
	 * @param		int		argY is the y-axis position for the new window
	 * @param		int		argWidth is the width for the new window
	 * @param		int		argHeight is the height for the new window
	 * @return		Window*	returns the created window.
	 */
	Window* Sandbox::NewWindow(int argRendererIndex, char* argPTitle, int argX, int argY, int argWidth, int argHeight)
	{
		Renderer* pRenderer = this->kernel->GetRenderer(argRendererIndex);

		if(pRenderer == 0) 
		{
			std::stringstream msg;
			msg << "Renderer with index " << argRendererIndex << " could not be found!"; 
			this->kernel->GetLogger()->Log((char*)msg.str().c_str(), Logger::LOG_LEVEL_ERROR, __FILE__, __LINE__);
		}

		Window* pWindow = this->kernel->GetWindowManager()->NewWindow(argPTitle, argX, argY, argWidth, argHeight);
		this->kernel->AddWindowRenderer(pWindow, pRenderer);

		return pWindow;
	}

	/**
	 * Creates a Scene and adds a window to the scene's collection.
	 * @param		int		argWindow is the window that needs to be added to the scene.
	 * @return		Scene*	returns the created scene.
	 */
	Scene* Sandbox::NewScene()
	{
		return this->kernel->GetSceneManager()->NewScene();
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