#include "../../Header Files/engine/N00b.h"

namespace engine
{
	//engine::N00b* n000by = new engine::N00b();
	//engine::Window* pWindow = n000by->NewWindow("I'm a noob window");
	//n000by->LoadScene("NoobScene", "mainScene.scene", pWindow);
	//n000by->Start();

	N00b::N00b()
	{
		this->kernel = new Kernel();
		Logger::AddStrategy(new ConsoleLog());
		Logger::AddStrategy(new TextLog());
		Logger::Log("Main: Initializing", Logger::INFO, __FILE__, __LINE__);
	}

	N00b::~N00b()
	{
		this->CleanUp();
	}

	void N00b::CleanUp()
	{
		if(this->kernel != NULL)
		{
			delete this->kernel;
		}
	}

	void N00b::Start()
	{
		Logger::Log("Main: Starting", engine::Logger::INFO, __FILE__, __LINE__);
		this->kernel->Start();
	}

	Window* N00b::NewWindow(std::string argTitle)
	{
		return this->NewWindow(argTitle, 100, 100, 800, 600);
	}

	Window* N00b::NewWindow(std::string argTitle, int argX, int argY, int argWidth, int argHeight)
	{
		//Default renderer.
		Renderer* pRenderer = this->kernel->GetRenderer(Renderer::DIRECTX_9);

		if(pRenderer == 0) 
		{
			char* msg = "Renderer with 888 could not be found";
			sprintf_s(msg, sizeof(msg), "Renderer with index %d could not be found", Renderer::DIRECTX_9);
			Logger::Log(msg, Logger::FATAL, __FILE__, __LINE__);
		}

		Window* pWindow = this->kernel->GetWindowManager()->NewWindow(argTitle, argX, argY, argWidth, argHeight);
		this->kernel->AddWindowRenderer(pWindow, pRenderer);
		this->kernel->GetInputManager()->SetupDevices(pWindow);

		return pWindow;
	}

	Scene* N00b::LoadScene(std::string argTitle, std::string argSceneFileName, Window* argPWindow)
	{
		Scene* pScene = this->kernel->LoadScene(argTitle, argSceneFileName);
		pScene->AddWindow(argPWindow);
		return pScene;
	}
}