#ifndef SANDBOX_H_
#define SANDBOX_H_

#include "Kernel.h"

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

		void NewWindow();


		//not sure if neccesary
		void CreateScene();
		void AddScene(Scene* argPScene);
		void RemoveScene(Scene* argPScene);

	};
}

#endif