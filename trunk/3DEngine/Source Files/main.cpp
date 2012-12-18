#include "..\Header Files\engine\Sandbox.h"
#include "..\Header Files\engine\logger\Logger.h"
#include "..\Header Files\engine\logger\ConsoleLog.h"

int main()
{
	// Create the engine
	engine::Sandbox* sandbox = new engine::Sandbox();
	// Add a log strategy
	engine::Logger::AddStrategy(new engine::ConsoleLog());


	// Create our scene
	//engine::Scene* scene1 = new SceneBas();
	// Add the scene to the engine
	//sandbox->AddScene("MainScene", scene1);
	// Add a window to the scene
	//scene1->AddWindow(sandbox->NewWindow(engine::Renderer::DIRECTX_9_RENDERER, "MainWindow", 100, 100, 800, 600));

	// load a scene file
	sandbox->LoadScene("MainScene", "mainScene.scene")
		->AddWindow(sandbox->NewWindow(engine::Renderer::DIRECTX_9_RENDERER, "MainWindow", 100, 100, 800, 600));


	// Start the engine (and load all the scenes(+entities) at the moment)
	sandbox->Start();
	return 0;
}