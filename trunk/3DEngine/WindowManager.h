#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_

#include <vector>
#include <algorithm>
#include "Win32Window.h"

namespace engine
{
	/**
	 * This class manages all created windows.
	 */
	class WindowManager
	{
	private:
		std::vector<Window*> windows;
	public:
		WindowManager();
		~WindowManager();
		void CleanUp();

		int GetWindowCount();
		Window* GetWindow(int index);
		std::vector<Window*> GetWindows();
		Window* NewWindow();
		void RemoveWindow(Window* argPWindow);
	};
}

#endif