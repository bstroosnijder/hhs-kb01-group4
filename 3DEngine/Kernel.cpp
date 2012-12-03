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
		Renderer* dx9renderer = new DirectX9Renderer(GetConsoleWindow());
		this->renderers.push_back(dx9renderer);

		this->winRenderer = std::map<Window*, Renderer*>();


		// UBER HACK!!!
		Scene* scene = this->sceneManager->NewScene();
		Window* window = this->windowManager->NewWindow();
		scene->AddWindow(window);
		this->winRenderer[window] = dx9renderer;
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

	void Kernel::Render()
	{
		// If there is at least one open window, we'll render that content
		if(this->windowManager->GetWindowCount() > 0)
		{
			// Loop through the scenes
			for each(Scene* scene in this->sceneManager->GetScenes())
			{
				// Loop through scene windows
				for each(Window* window in scene->GetWindows())
				{
					// render stuff here
					Renderer* renderer = this->winRenderer[window];
					renderer->Clear();
					renderer->BeginScene();
					scene->Draw(renderer);
					renderer->EndScene();
					renderer->Present(window);
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