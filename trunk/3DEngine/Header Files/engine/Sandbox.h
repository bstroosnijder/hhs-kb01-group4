#ifndef SANDBOX_H_
#define SANDBOX_H_

#include <string>
#include "logger\Logger.h"
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
		
		Window* Sandbox::NewWindow(int argRendererIndex, std::string argTitle, unsigned int argX, unsigned int argY, unsigned int argWidth, unsigned int argHeight);

		void CreateKeyboard(Window* argPWindow);

		Scene* GetScene(std::string argSceneName);
		Scene* LoadScene(std::string argSceneName, std::string argSceneFileName);
		void RemoveScene(std::string argSceneName);
	};
}

#endif