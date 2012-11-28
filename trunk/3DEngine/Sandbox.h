#ifndef Sandbox_H_
#define Sandbox_H_
#include "Kernel.h"
#include "ConsoleLog.h"

namespace engine
{
	/**
	 * This is a Sandbox. This a Facade.
	 * @author: Alex Hodes
	 */
	class Sandbox
	{
	private:
		Logger* logger;
		WindowManager* windowManager;
		SceneManager* sceneManager;
		Kernel* kernel;
	public:
		Sandbox();
		~Sandbox();
		void Start();
		void CreateWindow(int argWidth,int argHeight);
		//not sure if neccesary
		void CreateScene();
		void AddScene(engine::Scene* argScene);
		void RemoveScene(engine::Scene* argScene);

		void AddLogStrategy(engine::LogStrategy*);
		void RemoveLogStrategy(engine::LogStrategy*);
	};
}

#endif