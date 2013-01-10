#ifndef N00B_H_
#define N00B_H_

#include <string>
#include "logger\Logger.h"
#include "kernel\Kernel.h"
#include "scene\Scene.h"
#include "logger\Logger.h"
#include "logger\ConsoleLog.h"
#include "logger\TextLog.h"

namespace engine
{
	class N00b
	{
	private:
		Kernel* kernel;
	public:
		N00b();
		~N00b();

		void CleanUp();
		void Start();
		Window* NewWindow(std::string argTitle);
		Window* NewWindow(std::string argTitle, int argX, int argY, int argWidth, int argHeight);
		Scene* LoadScene(std::string argTitle, std::string argSceneFileName, Window* argPWindow);
	};
}

#endif