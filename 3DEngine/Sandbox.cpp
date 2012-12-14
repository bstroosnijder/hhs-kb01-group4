#include "Sandbox.h"

namespace engine
{
	//---Private attribute---
	//---Public attrubute---
	//---Private methods---
	//---Public methods---

	/**
	 * Constructs the Sandbox object.
	 */
	Sandbox::Sandbox()
	{
		this->kernel = new Kernel();
	}

	/**
	 * Destructs the Sandbox object.
	 */
	Sandbox::~Sandbox()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing this object.
	 * @return		void
	 */
	void Sandbox::CleanUp()
	{

	}

	/**
	 * Animate the Kernel, starting it's heartbeat.
	 * @return		void
	 */
	void Sandbox::Start()
	{
		this->kernel->LoadBeat();
		this->kernel->Start();
		engine::Logger::Log("Kernel Started", 1, __FILE__,__LINE__);
	}

	/**
	 * Creates a Scene and adds a window to the scene's collection.
	 * @param		char*				argPSceneName is the name of the new scene.
	 * @return		Scene*				returns the created scene.
	 */
	Scene* Sandbox::NewScene(char* argPSceneName)
	{
		return this->kernel->GetSceneManager()->NewScene(argPSceneName);
	}

	/**
	 * Removes a scene to the scene collection within the Scene manager
	 * @param		Scene*			argScene is the scene that will be removed in the collection
	 * @return		void
	 */
	void Sandbox::RemoveScene(char* argPSceneName)
	{
		this->kernel->GetSceneManager()->RemoveScene(argPSceneName);
	}

	/**
	 * Add a scene to the scene collection within the Scene manager
	 * @param		char*			argPSceneName is the identifier for the scene in the collection
	 * @param		Scene*			Scene is the scene that will be added to the scene collection
	*/
	void Sandbox::AddScene(char* argPSceneName, Scene* argPScene)
	{
		this->kernel->GetSceneManager()->AddScene(argPSceneName, argPScene);
	}

	/**
	 * Gets a scene from the collection by it's name.
	 * @param		char*		argPSceneName is the identifier for the scene in the collection
	*/
	Scene* Sandbox::GetScene(char* argPSceneName)
	{
		return this->kernel->GetSceneManager()->GetScene(argPSceneName);
	}

	/**
	 * Creates a Window and creates the association with this Window and the Renderer object.
	 * @param		int					argRendererIndex is the index of the renderer to be added to the window we're creating.
	 * @param		char*				argPTitle is the title for the new window
	 * @param		int					argX is the x-axis position for the new window
	 * @param		int					argY is the y-axis position for the new window
	 * @param		int					argWidth is the width for the new window
	 * @param		int					argHeight is the height for the new window
	 * @return		Window*				returns the created window.
	 */
	Window* Sandbox::NewWindow(int argRendererIndex, char* argPTitle, unsigned int argX, unsigned int argY, unsigned int argWidth, unsigned int argHeight)
	{
		Renderer* pRenderer = this->kernel->GetRenderer(argRendererIndex);

		if(pRenderer == 0) 
		{
			char* msg = "Renderer with 888 could not be found";
			sprintf_s(msg, sizeof(msg), "Renderer with index %d could not be found", argRendererIndex);
			Logger::Log(msg, Logger::LOG_LEVEL_ERROR, __FILE__, __LINE__);
		}

		Window* pWindow = this->kernel->GetWindowManager()->NewWindow(argPTitle, argX, argY, argWidth, argHeight);
		this->kernel->AddWindowRenderer(pWindow, pRenderer);

		return pWindow;
	}
}