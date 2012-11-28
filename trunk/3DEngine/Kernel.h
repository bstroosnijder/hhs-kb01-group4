#ifndef KERNEL_H_
#define KERNEL_H_

#include "stdlib.h"
#include "WindowManager.h"
#include "Logger.h"
#include "TextLog.h"
#include "ConsoleLog.h" 
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"

namespace engine {
	class Kernel
	{
	private:
		//Private attributes
		Logger logger;
		WindowManager* windowManager;
		SceneManager* sceneManager;
		ResourceManager* resourceManager;
		InputManager* inputManager;
	public:
		//Public methods
		Kernel(void);
		~Kernel(void);
		void Run(void);
		Logger GetLogger(void);
	};
}
#endif

