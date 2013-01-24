#include "../../Header Files/engine/N00b.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---

	/**
	 * Create a new Window with default values.
	 * @return		Window*
	 */
	Window* N00b::NewWindow()
	{
		//Default renderer.
		Renderer* pRenderer = this->kernel->GetRenderer(Renderer::DIRECTX_9);
		
		//Default window settings.
		std::string title = "Main window";
		unsigned int x = 100;
		unsigned int y = 100;
		unsigned int width = 800;
		unsigned int height = 800;

		//If the renderer could not be found...
		if(pRenderer == 0) 
		{
			//...Log this and let the exception come naturally.
			char* msg = "Renderer with 888 could not be found";
			sprintf_s(msg, sizeof(msg), "Renderer with index %d could not be found", Renderer::DIRECTX_9);
			Logger::Log(msg, Logger::FATAL, __FILE__, __LINE__);
		}

		//Create a new window with the default title, x, y, width and height.
		Window* pWindow = this->kernel->GetWindowManager()->NewWindow(title, x, y, width, height);
		//Finally, create a link between this window and that renderer.
		this->kernel->AddWindowRenderer(pWindow, pRenderer);

		return pWindow;
	}

	//---Public methods---

	/**
	 * Construct the SceneManager object.
	 */
	N00b::N00b()
	{
		this->kernel = new Kernel();
		Logger::AddStrategy(new ConsoleLog());
		Logger::AddStrategy(new TextLog());
		Logger::Log("N00b: Initializing", Logger::INFO, __FILE__, __LINE__);
	}

	/**
	 * Destructs the SceneManager object.
	 */
	N00b::~N00b()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void N00b::CleanUp()
	{
		if(this->kernel != NULL)
		{
			delete this->kernel;
		}
	}

	/**
	 * Starts the engine.
	 * @return		void
	 */
	void N00b::Start()
	{
		Logger::Log("N00b: Starting", engine::Logger::INFO, __FILE__, __LINE__);
		this->kernel->Start();
	}

	/**
	 * Loads a scene based on a scene file name.
	 * @param		std::string		The name of the scene file.
	 * @return		Scene*
	 */
	void N00b::LoadScene(std::string argSceneFileName)
	{
		//Default scene title
		std::string title = "defaultScene";
		this->LoadScene(title, argSceneFileName);
	}

	/**
	 * Loads a scene based on a scene title (key) and a scene file name.
	 * @param		std::string		The title to be associated with the created scene.
	 * @param		std::string		The name of the scene file.
	 * @return		Scene*
	 */
	void N00b::LoadScene(std::string argTitle, std::string argSceneFileName)
	{ 
		//Create a new window with default values.
		Window* pWindow = this->NewWindow();
		//Set up the input devices for the given window, so that keyboard, mouse and joystick input will be handled for that window.
		this->kernel->GetInputManager()->SetupDevices(pWindow);
		//Tell the kernel to load a scene based on the a specified filename and give the scene the specified title.
		Scene* pScene = this->kernel->LoadScene(argTitle, argSceneFileName);

		// Check if the scene is actually created
		if(pScene == NULL)
		{
			Logger::Log("Unable to create scene", engine::Logger::INFO, __FILE__, __LINE__);
			std::system("pause");
			std::exit(-1);
		}

		//Add the window to the scene, making sure the created scene has at least one window to display itself in.
		pScene->AddWindow(pWindow);
	}
}