#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_

#include <map>
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
		static std::map<HWND, Window*> windows;
	public:
		WindowManager();
		~WindowManager();
		void CleanUp();

		int GetWindowCount();
		Window* GetWindow(HWND argHWND);
		std::map<HWND, Window*> GetWindows();
		Window* NewWindow();
		Window* NewWindow(char* argPTitle, int argX, int argY, int argWidth, int argHeight);
		static void RemoveWindow(HWND argHWND);
		static LRESULT WINAPI MsgProc(HWND argHWin, UINT argMsg, WPARAM argWParam, LPARAM argLParam);
	};
}

#endif