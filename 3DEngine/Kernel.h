#ifndef KERNEL_H_
#define KERNEL_H_

#include <vector>
#include "WindowManager.h"
#include "DirectX9Renderer.h"
#include "Logger.h"
#include "Renderer.h"
#include "TextLog.h"
#include "ConsoleLog.h" 
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"

namespace engine {
	/**
	 * This class is responsible for managing the entire engine.
	 * It will check the status of, and communicate with all the sub-managers.
	 * These sub-managers are in turn responsible for running their respective parts of the engine.
	 */
	class Kernel
	{
	private:
		Logger logger;
		std::vector<Renderer*> renderers;
		WindowManager* windowManager;
		SceneManager* sceneManager;
		ResourceManager* resourceManager;
		InputManager* inputManager;
	public:
		Kernel();
		~Kernel();
		void Run();
		Logger GetLogger();
	};
}
#endif

