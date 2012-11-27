#include "Kernel.h"

static Logger textLogger; 
static Logger consoleLogger;
engine::Kernel::Kernel(void)
{
	WindowManager* windowManager = new WindowManager();
	//SceneManager* sceneManager = new SceneManager();
	LogStrategy* textStrat = new TextLog();
	LogStrategy* consoleStrat = new ConsoleLog();

	textLogger.AddStrategy(textStrat);
	consoleLogger.AddStrategy(consoleStrat);

}


engine::Kernel::~Kernel(void)
{
}
