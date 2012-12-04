#include "WindowManager.h"

namespace engine
{
	//---Private attributes---

	std::map<HWND, Window*> WindowManager::windows = std::map<HWND, Window*>();

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
		return WindowManager::windows.size();
	}

	/**
	 * Obtain all the Window pointers in the windows collection.
	 * @return		std::vector<Window*>		The entire scene collection.
	 */
	std::map<HWND, Window*> WindowManager::GetWindows()
	{
		return WindowManager::windows;
	}

	/**
	 * MakeWindow creates a window for the application and shows it.
	 * @param		char*	argPTitle is the title for the new window
	 * @param		int		argX is the x-axis position for the new window
	 * @param		int		argY is the y-axis position for the new window
	 * @param		int		argWidth is the width for the new window
	 * @param		int		argHeight is the height for the new window
	 * @return		Window*		The created window.
	 */
	Window* WindowManager::NewWindow(char* argPTitle, unsigned int argX, unsigned int argY, unsigned int argWidth, unsigned int argHeight)
	{
		Window* pWindow;
		#ifdef _WIN32
		// Windows 32bit
		pWindow = new Win32Window(argPTitle, argX, argY, argWidth, argHeight);
		#elif _WIN64
		// Windows 64bit
		pWindow = new Win32Window(argPTitle, argX, argY, argWidth, argHeight);
		#endif
		WindowManager::windows[((Win32Window*)pWindow)->GetHWin()] = pWindow;
		return pWindow;
	}

	/**
	 * Remove a Window pointer from the scenes collection.
	 * @param		Window*						The Window pointer to remove from the collection of scenes.
	 * @return		void
	 */
	void WindowManager::RemoveWindow(HWND argHWND)
	{
		WindowManager::windows.erase(argHWND);
	}
	
	/**
	 * Listen to what windows tells our window
	 * @param		HWND		The window handle to the window
	 * @param		UINT		halp?
	 * @param		WPARAM		halp?
	 * @param		LPARAM		halp?
	 * @return		LRESULT		halp?
	 */
	LRESULT WINAPI WindowManager::MsgProc(HWND argHWin, UINT argMsg, WPARAM argWParam, LPARAM argLParam)
	{
		switch(argMsg)
		{
			case WM_DESTROY:
				PostQuitMessage(0);
				WindowManager::RemoveWindow(argHWin);
				return 0;
		}

		return DefWindowProc(argHWin, argMsg, argWParam, argLParam);
	}
}