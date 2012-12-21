#ifndef SANDBOX_H_
#define SANDBOX_H_

#include <string>
#include "kernel\Kernel.h"
#include "scene\Scene.h"

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
		
		Scene* GetScene(std::string argSceneName);
		void AddScene(std::string argSceneName, Scene* argScene);
		Scene* LoadScene(std::string argSceneName, std::string argSceneFileName);
		void RemoveScene(std::string argSceneName);
		void CreateKeyboard(Window* argPWindow);
		
		Window* Sandbox::NewWindow(int argRendererIndex, std::string argTitle, unsigned int argX, unsigned int argY, unsigned int argWidth, unsigned int argHeight);
	};
}

#endif