#ifndef SANDBOX_H_
#define SANDBOX_H_

#include "Kernel.h"
#include "Scene.h"

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
		void Start();
		
		Scene* NewScene(char* argPSceneName);
		void RemoveScene(char* argPSceneName);
		void AddScene(char* argPSceneName, Scene* argPScene);
		Scene* LoadScene(char* argPFileName);
		Scene* GetScene(char* argPSceneName);
		
		Window* Sandbox::NewWindow(int argRendererIndex, char* argPTitle, unsigned int argX, unsigned int argY, unsigned int argWidth, unsigned int argHeight);
	};
}

#endif