#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_

#include <map>
#include <string>
#include "..\logger\Logger.h"
#include "..\window\Win32Window.h"

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
		std::map<HWND, Window*> GetWindows();
		Window* NewWindow(std::string argTitle, unsigned int argX, unsigned int argY, unsigned int argWidth, unsigned int argHeight);
		static void RemoveWindow(HWND argHWND);
		static LRESULT WINAPI MsgProc(HWND argHWin, UINT argMsg, WPARAM argWParam, LPARAM argLParam);
	};
}

#endif