#ifndef SANDBOX_H_
#define SANDBOX_H_

#include "Kernel.h"
#include <sstream>

namespace engine
{
	/**
	 * This is a Sandbox. This a Facade.
	 * @author: Alex Hodes
	 */
	class Sandbox
	{
	private:
		Kernel* kernel;
	public:
		Sandbox();
		~Sandbox();
		void CleanUp();
		void HeartBeat();
		
		void AddLogStrategy(LogStrategy* argPLogStrat);
		void RemoveLogStrategy(LogStrategy* argPLogStrat);

		Window* NewWindow(int argRendererIndex);
		Window* Sandbox::NewWindow(int argRendererIndex, char* argPTitle, int argX, int argY, int argWidth, int argHeight);
		Scene* NewScene(Window* argPWindow);
		//not sure if neccesary
		
		void AddScene(Scene* argPScene);
		void RemoveScene(Scene* argPScene);
	};
}

#endif