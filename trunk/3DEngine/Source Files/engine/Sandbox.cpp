#include "..\..\Header Files\engine\Sandbox.h"

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
		if(this->kernel != NULL)
		{
			delete this->kernel;
		}
	}

	/**
	 * Animate the Kernel, starting it's heartbeat.
	 * @return		void
	 */
	void Sandbox::Start()
	{
		this->kernel->Start();
	}

	/**
	 * Creates a Window and creates the association with this Window and the Renderer object.
	 * @param		int				argRendererIndex is the index of the renderer to be added to the window we're creating.
	 * @param		char*			argPTitle is the title for the new window
	 * @param		int				argX is the x-axis position for the new window
	 * @param		int				argY is the y-axis position for the new window
	 * @param		int				argWidth is the width for the new window
	 * @param		int				argHeight is the height for the new window
	 * @return		Window*			returns the created window.
	 */
	Window* Sandbox::NewWindow(int argRendererIndex, std::string argTitle, unsigned int argX, unsigned int argY, unsigned int argWidth, unsigned int argHeight)
	{
		Renderer* pRenderer = this->kernel->GetRenderer(argRendererIndex);

		if(pRenderer == 0) 
		{
			char* msg = "Renderer with 888 could not be found";
			sprintf_s(msg, sizeof(msg), "Renderer with index %d could not be found", argRendererIndex);
			Logger::Log(msg, Logger::FATAL, __FILE__, __LINE__);
		}

		Window* pWindow = this->kernel->GetWindowManager()->NewWindow(argTitle, argX, argY, argWidth, argHeight);
		this->kernel->AddWindowRenderer(pWindow, pRenderer);

		return pWindow;
	}

	/**
	 * iets
	 * @param		Window*			The window to hook input listening to
	 * @return		void
	 */
	void Sandbox::SetupDevices(Window* argPWindow)
	{
		this->kernel->GetInputManager()->SetupDevices(argPWindow);
	}

	/**
	 * Gets a scene from the collection by it's name.
	 * @param		char*			the identifier for the scene in the collection
	*/
	Scene* Sandbox::GetScene(std::string argSceneName)
	{
		return this->kernel->GetSceneManager()->GetScene(argSceneName);
	}
	
	/**
	 * Loads a scene file into a scene
	 * @param		std::string		The identifier for the scene in the collection
	 * @param		std::string		The scene file to load
	 * @return		Scene*
	 */
	Scene* Sandbox::LoadScene(std::string argSceneName, std::string argSceneFileName)
	{
		return this->kernel->LoadScene(argSceneName, argSceneFileName);
	}

	/**
	 * Removes a scene to the scene collection within the Scene manager
	 * @param		std::string		is the scene that will be removed in the collection
	 * @return		void
	 */
	void Sandbox::RemoveScene(std::string argSceneName)
	{
		this->kernel->GetSceneManager()->RemoveScene(argSceneName);
	}
}