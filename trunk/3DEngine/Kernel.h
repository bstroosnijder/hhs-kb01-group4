#ifndef KERNEL_H_
#define KERNEL_H_

#include <map>
#include <sstream>
#include "Logger.h"
#include "ConsoleLog.h"
#include "TextLog.h"
#include "WindowManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "DirectX9Renderer.h"

namespace engine
{
	/**
	 * This class is responsible for managing the entire engine.
	 * It will check the status of, and communicate with all the sub-managers.
	 * These sub-managers are in turn responsible for running their respective parts of the engine.
	 */
	class Kernel
	{
	private:
		static Logger* logger;
		WindowManager* windowManager;
		SceneManager* sceneManager;
		ResourceManager* resourceManager;
		InputManager* inputManager;
		std::vector<Renderer*> renderers;
		std::map<Window*, Renderer*> winRenderer;
	public:
		Kernel();
		~Kernel();
		void CleanUp();
		static Logger* GetLogger();
		Renderer* GetRenderer(int argIndex);
		WindowManager* GetWindowManager();
		SceneManager* GetSceneManager();
		ResourceManager* GetResourceManager();
		InputManager* GetInputManager();
		void AddWindowRenderer(Window* argWindow, Renderer* argRenderer);
		void Render();
		void HeartBeat();
	};
}
#endif

