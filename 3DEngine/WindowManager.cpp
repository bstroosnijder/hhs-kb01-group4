#include "WindowManager.h"
#include "Win32Window.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Constructor for Window class.
	 */
	WindowManager::WindowManager()
	{

	}

	/**
	 * Destructor for Window class.
	 * @return	void
	 */
	WindowManager::~WindowManager()
	{

	}

	/**
	 * MakeWindow creates a window for the application and shows it.
	 * @param	argWidth	Defines the width of the window.
	 * @param	argHeight	Defines the height of the window.
	 * @return	void
	 */
	void WindowManager::NewWindow(const unsigned int argWidth, const unsigned int argHeight)
	{
		//Create a new Win32Window object and initialize it with a width and a height.
		Win32Window* window = new Win32Window(argWidth, argHeight);
		window->Show();
	}
}
