#include "Kernel.h"

namespace engine
{
	//---Private attributes---

	Logger* Kernel::logger = new Logger();

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
		// Initialize the managers
		this->windowManager = new WindowManager();
		this->sceneManager = new SceneManager();
		this->resourceManager = new ResourceManager();
		this->inputManager = new InputManager();

		//Initialise and fill the renderers vector with the default renderers.
		this->renderers = std::vector<Renderer*>();
		this->renderers.push_back(new DirectX9Renderer(GetConsoleWindow()));

		//Initialise the map that associates windows with renderers.
		this->winRenderer = std::map<Window*, Renderer*>();
	}

	/**
	 * Destructs the Kernel object.
	 * @return		void
	 */
	Kernel::~Kernel()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing this object.
	 * @return		void
	 */
	void Kernel::CleanUp()
	{
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

        while(this->windowManager->GetWindowCount() > 0)
        {
            if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
            {				
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
			else
			{
				this->HeartBeat();
			}
        }

		//There are no more windows, application closes.
		this->CleanUp();
	}

	void Kernel::LoadBeat()
	{
		std::map<char*, Scene*> scenes = this->sceneManager->GetScenes();
		std::map<char*, Scene*>::iterator it;
		for(it = scenes.begin(); it != scenes.end(); it++)
		{
			Scene* pScene = it->second;
			for each(Window* pWindow in pScene->GetWindows())
			{
				Renderer* pRenderer = this->winRenderer[pWindow];
				pScene->Load(this->resourceManager, pRenderer);
			}
		}
	}

	/**
	 * Loop through all scenes and their windows to render them.
	 * @return		void
	 */
	void Kernel::HeartBeat()
	{
		std::map<char*, Scene*> scenes = this->sceneManager->GetScenes();
		std::map<char*, Scene*>::iterator it;
		for(it = scenes.begin(); it != scenes.end(); it++)
		{
			Scene* pScene = it->second;
			pScene->Update();

			// Loop through scene windows
			for each(Window* pWindow in pScene->GetWindows())
			{
				//Render the content of this window.
				Renderer* pRenderer = this->winRenderer[pWindow];
				pRenderer->Clear();
				pRenderer->BeginScene();

				pRenderer->SetupWorldMatrix();
				pRenderer->SetupViewMatrix();
				pRenderer->SetupProjectionMatrix();

				pScene->Draw(pRenderer);

				pRenderer->EndScene();
				pRenderer->Present(pWindow);
			}
		}
	}

	/**
	 * Obtain the Logger object associated with the Kernel.
	 * @return		Logger*
	 */
	Logger* Kernel::GetLogger()
	{
		return logger;
	}

	/**
	 * Get the renderer on the specified index.
	 * @param		unsigned int		The index of the renderer to return.
	 * @return		Renderer*
	 */
	Renderer* Kernel::GetRenderer(unsigned int argIndex)
	{
		if(argIndex < this->renderers.size()) 
		{
			return this->renderers[argIndex];
		}
		else
		{
			return 0;
		}
	}

	/**
	 * Obtain the WindowManager object.
	 * @return		WindowManager*	
	 */
	WindowManager* Kernel::GetWindowManager()
	{
		return this->windowManager;
	}
	
	/**
	 * Obtain the SceneManager object.
	 * @return		SceneManager*
	 */
	SceneManager* Kernel::GetSceneManager()
	{
		return this->sceneManager;
	}
	
	/**
	 * Obtain the ResourceManager object.
	 * @return		ResourceManager*
	 */
	ResourceManager* Kernel::GetResourceManager()
	{
		return this->resourceManager;
	}
	
	/**
	 * Obtain the InputManager object.
	 * @return		InputManager*
	 */
	InputManager* Kernel::GetInputManager()
	{
		return this->inputManager;
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