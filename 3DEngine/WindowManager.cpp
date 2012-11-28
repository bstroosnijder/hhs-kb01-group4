#include "WindowManager.h"
#include "Win32Window.h"


engine::WindowManager::WindowManager()
{
}


engine::WindowManager::~WindowManager()
{
}

void engine::WindowManager::MakeWindow(const unsigned int argWidth, const unsigned int argHeight)
{
	// Create a new Win32Window object and initialize it with a width and a height.
	Win32Window* window = new Win32Window(argWidth, argHeight);
	window->Show();
}
