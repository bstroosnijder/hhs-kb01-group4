#ifndef N00B_H_
#define N00B_H_

#include <string>
#include "logger\Logger.h"
#include "kernel\Kernel.h"
#include "scene\Scene.h"
#include "logger\Logger.h"
#include "logger\ConsoleLog.h"
#include "logger\TextLog.h"

/**
 * This is the 'N00b'. This class is responsible for the communication between the engine and the game developer.
 * As the name of the class suggests, this Facade is for the weak-minded.
 * If you value freedom, flexibility and customization, we strongly recommend you not to use this class to communicate with the engine.
 * Use Sandbox instead. Trust us...
 * Just do it.
 */

namespace engine
{
	class N00b
	{
	private:
		Kernel* kernel;

		Window* NewWindow();
	public:
		N00b();
		~N00b();

		void CleanUp();
		void Start();
		
		void LoadScene(std::string argSceneFileName);
		void LoadScene(std::string argTitle, std::string argSceneFileName);
	};
}

#endif