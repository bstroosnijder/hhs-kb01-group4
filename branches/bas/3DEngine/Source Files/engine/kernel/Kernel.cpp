#include "..\..\..\Header Files\engine\kernel\Kernel.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Constructs the Kernel object, initialising every included module's manager.
	 * In addition, the renderer vector is initialised and filled with the default renderers the system has to offer.
	 * Finally, the map that associates windows with renderers is initialised.
	 */
	Kernel::Kernel()
	{
		Logger::Log("Kernel: Initializing", Logger::INFO, __FILE__, __LINE__);
		
		// Initialize the managers
		this->pWindowManager	= new WindowManager();
		this->pResourceManager	= new ResourceManager();
		this->pInputManager		= new InputManager();
		this->pSceneManager		= new SceneManager();

		//Initialise and fill the renderers map with the default renderers.
		this->renderers			= std::map<unsigned int, Renderer*>();
		this->renderers[Renderer::DIRECTX_9] = new DirectX9Renderer(GetConsoleWindow());

		//Initialise the map that associates windows with renderers.
		this->winRenderer		= std::map<Window*, Renderer*>();

		Logger::Log("Kernel: Finished", Logger::INFO, __FILE__, __LINE__);
	}

	/**
	 * Destructs the Kernel object.
	 */
	Kernel::~Kernel()
	{
		Logger::Log("Kernel: Disposing", Logger::INFO, __FILE__, __LINE__);
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing this object.
	 * @return		void
	 */
	void Kernel::CleanUp()
	{
		if(this->pWindowManager != NULL)
		{
			delete this->pWindowManager;
		}

		if(this->pResourceManager != NULL)
		{
			delete this->pResourceManager;
		}

		if(this->pInputManager != NULL)
		{
			delete this->pInputManager;
		}

		if(this->pSceneManager != NULL)
		{
			delete this->pSceneManager;
		}

		std::map<unsigned int, Renderer*>::iterator itRenderers;
		for(itRenderers = this->renderers.begin(); itRenderers != this->renderers.end(); itRenderers++)
		{
			delete itRenderers->second;
		}
		this->renderers.clear();

		this->winRenderer.clear();
	}

	/**
	 * The heartbeat makes sure that the windows will be rendered.
	 * It provides the application with a loop and an exit condition...
	 * ...which will pulse like a heartbeat to either render or manage what ever is needed.
	 * @return		void
	 */
	void Kernel::Start()
	{
		MSG msg;
        ZeroMemory(&msg, sizeof(msg));

		// Check if we have unloaded scenes, and sets them up with a SceneBuilder
		std::map<std::string, Scene*> scenes = this->pSceneManager->GetScenes();
		std::map<std::string, Scene*>::iterator sceneIt;
		for(sceneIt = scenes.begin(); sceneIt != scenes.end(); sceneIt++)
		{
			std::string sceneName	= sceneIt->first;
			Scene* pScene			= sceneIt->second;

			if(!pScene->isLoaded())
			{
				Logger::Log("Kernel: Unloaded scene found, Starting SceneBuilder", Logger::INFO, __FILE__, __LINE__);
				SceneBuilder* pSceneBuilder = new SceneBuilder(sceneName, pScene,
					this->pResourceManager, this->renderers[Renderer::DIRECTX_9]);

				Keyboard* pKeyboard = this->pInputManager->GetKeyboard();
				pKeyboard->AddInputListener(pScene->GetCamera());
				pKeyboard->AddBind("KEY_W",					"move_forward");
				pKeyboard->AddBind("KEY_S",					"move_backward");
				pKeyboard->AddBind("KEY_Q",					"move_left");
				pKeyboard->AddBind("KEY_E",					"move_right");
				pKeyboard->AddBind("KEY_SPACE",				"move_up");
				pKeyboard->AddBind("KEY_LSHIFT",			"move_down");
				pKeyboard->AddInputListener(pSceneBuilder);
				pKeyboard->AddBind("KEY_LCONTROL:KEY_E",	"spawn");
				pKeyboard->AddBind("KEY_LCONTROL:KEY_L",	"load");
				pKeyboard->AddBind("KEY_LCONTROL:KEY_M",	"modify");
				pKeyboard->AddBind("KEY_LCONTROL:KEY_D",	"delete");
				pKeyboard->AddBind("KEY_LCONTROL:KEY_C",	"clear");
				pKeyboard->AddBind("KEY_LCONTROL:KEY_S",	"save");

				Mouse* pMouse = this->pInputManager->GetMouse();
				pMouse->AddInputListener(pScene->GetCamera());
				pMouse->AddBind("MOUSE_X",					"turn_left_right");
				pMouse->AddBind("MOUSE_Y",					"pan_up_down");
				//pMouse->AddInputListener(pSceneBuilder);
			}
		}


        while(this->pWindowManager->GetWindowCount() > 0)
        {
            if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
            {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
            }
			else
			{
				this->HeartBeat();
				this->pInputManager->InputBeat();
			}
        }

		//There are no more windows, application closes.
		this->CleanUp();
	}

	/**
	 * Loop through all scenes and their windows to render them.
	 * @return		void
	 */
	void Kernel::HeartBeat()
	{
		std::map<std::string, Scene*> scenes = this->pSceneManager->GetScenes();
		std::map<std::string, Scene*>::iterator sceneIt;
		for(sceneIt = scenes.begin(); sceneIt != scenes.end(); sceneIt++)
		{
			std::string sceneName	= sceneIt->first;
			Scene* pScene			= sceneIt->second;

			// Update the scene
			pScene->Update();

			// Loop through scene windows
			std::list<Window*> windows = pScene->GetWindows();
			std::list<Window*>::iterator windowIt;
			for(windowIt = windows.begin(); windowIt != windows.end(); windowIt++)
			{
				Window* pWindow = *windowIt;
				// Add to the window title
				pWindow->AddTitle(sceneName);

				// Render the content of this window.
				Renderer* pRenderer = this->winRenderer[pWindow];
				pRenderer->Clear();
				pRenderer->BeginScene();
				// Draw the scene
				pScene->Draw(pRenderer);
				pRenderer->EndScene();
				pRenderer->Present(pWindow);
			}
		}
	}

	/**
	 * Get the renderer on the specified index.
	 * @param		unsigned int		The index of the renderer to return.
	 * @return		Renderer*
	 */
	Renderer* Kernel::GetRenderer(unsigned int argIndex)
	{
		return this->renderers[argIndex];
	}

	/**
	 * Obtain the WindowManager object.
	 * @return		WindowManager*	
	 */
	WindowManager* Kernel::GetWindowManager()
	{
		return this->pWindowManager;
	}
	
	/**
	 * Obtain the ResourceManager object.
	 * @return		ResourceManager*
	 */
	ResourceManager* Kernel::GetResourceManager()
	{
		return this->pResourceManager;
	}
	
	/**
	 * Obtain the InputManager object.
	 * @return		InputManager*
	 */
	InputManager* Kernel::GetInputManager()
	{
		return this->pInputManager;
	}
	
	/**
	 * Obtain the SceneManager object.
	 * @return		SceneManager*
	 */
	SceneManager* Kernel::GetSceneManager()
	{
		return this->pSceneManager;
	}

	/**
	 * This function passes the load command throu to the scene manager for each of the renderer
	 * @param		std::string		The name of the scene
	 * @param		std::string		The filename of the scene
	 * @return		Scene*
	 */
	Scene* Kernel::LoadScene(std::string argSceneName, std::string argSceneFileName)
	{
		return this->pSceneManager->LoadScene(this->pResourceManager, this->pInputManager,
			this->renderers[0], argSceneName, argSceneFileName);
	}

	/**
	 * Add a renderer to the winRenderer map with window as the key.
	 * @param		argPWindow			The Window pointer serving as key for the winRenderer map entry.
	 * @param		argPRenderer		The Renderer pointer serving as value for the winRenderer map entry.
	 * @return		void
	 */
	void Kernel::AddWindowRenderer(Window* argPWindow, Renderer* argPRenderer)
	{
		this->winRenderer[argPWindow] = argPRenderer;
	}
}