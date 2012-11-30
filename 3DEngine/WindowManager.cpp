#include "WindowManager.h"

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
		this->windows = std::vector<Window*>();
	}

	/**
	 * Destructor for Window class.
	 */
	WindowManager::~WindowManager()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void WindowManager::CleanUp()
	{
	}

	/**
	 * Returns the number of windows currently in the windows vector
	 * @return		int
	 */
	int WindowManager::GetWindowCount()
	{
		return this->windows.size();
	}

	/**
	 * Obtain all the Window pointers in the windows collection.
	 * @return		std::vector<Window*>		The entire scene collection.
	 */
	std::vector<Window*> WindowManager::GetWindows()
	{
		return this->windows;
	}

	/**
	 * MakeWindow creates a window for the application and shows it.
	 * @param		argWidth					Defines the width of the window.
	 * @param		argHeight					Defines the height of the window.
	 * @return		Window*
	 */
	Window* WindowManager::NewWindow()
	{
		Window* window;
#ifdef _WIN32
		// Windows 32bit
		window = new Win32Window();
#elif _WIN64
		// Windows 64bit
		window = new Win32Window();
#endif
		this->windows.push_back(window);
		return window;
	}

	/**
	 * Remove a Window pointer from the scenes collection.
	 * @param		Window*						The Window pointer to remove from the collection of scenes.
	 * @return		void
	 */
	void WindowManager::RemoveWindow(Window* argPWindow)
	{
		//Find the position of the given window and store it in 'position'.
		//Position is set equal to windows.end() when the object can't be found.
		std::vector<Window*>::iterator position = std::find(this->windows.begin(), this->windows.end(), argPWindow);

		if(position != this->windows.end()) 
		{
			this->windows.erase(position);
		}
	}
}
