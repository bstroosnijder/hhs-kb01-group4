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
		
		Window* Sandbox::NewWindow(int argRendererIndex, char* argPTitle, unsigned int argX, unsigned int argY, unsigned int argWidth, unsigned int argHeight);
		Scene* NewScene();
		
		void AddScene(Scene* argPScene);
		void RemoveScene(Scene* argPScene);
	};
}

#endif