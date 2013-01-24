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
 * It is a simplified version with ease of use and a quick startup in mind.
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