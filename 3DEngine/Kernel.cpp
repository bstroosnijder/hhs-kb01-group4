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
		this->logger = new Logger();

		// Initialize the managers
		this->windowManager = new WindowManager();
		this->sceneManager = new SceneManager();
		this->resourceManager = new ResourceManager();
		this->inputManager = new InputManager();

		this->renderers = std::vector<Renderer*>();
		Renderer* pDx9renderer = new DirectX9Renderer(GetConsoleWindow());
		this->renderers.push_back(pDx9renderer);

		this->winRenderer = std::map<Window*, Renderer*>();
	}

	/**
	 * Destruct the Kernel object.
	 * @return		void
	 */
	Kernel::~Kernel()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void Kernel::CleanUp()
	{
	}

	/**
	 * Obtain the Logger object associated with the Kernel.
	 * @return		logger		Returns the logger associated with the kernel.
	 */
	Logger* Kernel::GetLogger()
	{
		return this->logger;
	}

	/**
	 * Get the renderer on the specified index.
	 * @param		argIndex		The index of the renderer to return.
	 * @return		Renderer*
	 */
	Renderer* Kernel::GetRenderer(int argIndex)
	{
		if(argIndex >= 0 && argIndex < this->renderers.size()) 
		{
			return this->renderers[argIndex];
		}
		else
		{
			return 0;
		}
	}

	/**
	 * Getter
	 * @return		WindowManager*
	 */
	WindowManager* Kernel::GetWindowManager()
	{
		return this->windowManager;
	}
	
	/**
	 * Getter
	 * @return		SceneManager*
	 */
	SceneManager* Kernel::GetSceneManager()
	{
		return this->sceneManager;
	}
	
	/**
	 * Getter
	 * @return		ResourceManager*
	 */
	ResourceManager* Kernel::GetResourceManager()
	{
		return this->resourceManager;
	}
	
	/**
	 * Getter
	 * @return		InputManager*
	 */
	InputManager* Kernel::GetInputManager()
	{
		return this->inputManager;
	}

	/**
	 * Add a renderer to the winRenderer map, with window as the key.
	 * @param	argPWindow		The Window pointer serving as key for the winRenderer map entry.
	 * @param	argPRenderer	The Renderer pointer serving as value for the winRenderer map entry.
	 * @return	void
	 */
	void Kernel::AddWindowRenderer(Window* argPWindow, Renderer* argPRenderer)
	{
		this->winRenderer[argPWindow] = argPRenderer;
	}

	void Kernel::Render()
	{
		// If there is at least one open window, we'll render that content
		if(this->windowManager->GetWindowCount() > 0)
		{
			// Loop through the scenes
			for each(Scene* pScene in this->sceneManager->GetScenes())
			{
				// Loop through scene windows
				for each(Window* pWindow in pScene->GetWindows())
				{
					// render stuff here
					Renderer* pRenderer = this->winRenderer[pWindow];
					pRenderer->Clear();
					pRenderer->BeginScene();
					pScene->Draw(pRenderer);
					pRenderer->EndScene();
					pRenderer->Present(pWindow);
				}
			}
		}
	}

	/**
	 * The heartbeat makes sure that the windows will be rendered. 
	 * It also check of there is a window created. If it does it renders. If it does not nothing happens.
	 * Yeah this is dog. Sorry for the mess ;'(
	 * @return	void
	 */
	void Kernel::HeartBeat()
	{
		MSG msg;
        ZeroMemory(&msg, sizeof(msg));

        while(msg.message != WM_QUIT)
        {
            if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
			else
			{
				this->Render();
			}
        }
		// no loop, no pulse
		this->CleanUp();
	}
}