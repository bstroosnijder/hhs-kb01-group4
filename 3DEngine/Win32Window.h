#ifndef WIN32WINDOW_H_
#define WIN32WINDOW_H_

#include <Windows.h>
#include "Window.h"

namespace engine
{
	/**
	 * This class creates a window specificly for the Windows Operating System and implements the Window interface.
	 */
	class Win32Window : public Window
	{
	private:
		HWND hWin;
	public:
		Win32Window();
		~Win32Window();
		void CleanUp();
		static LRESULT WINAPI MsgProc(HWND argHWin, UINT argMsg, WPARAM argWParam, LPARAM argLParam);
		void SetTitle(char* argTitle);
		char* GetTitle();
		void SetX(unsigned int argX);
		unsigned int GetX();
		void SetY(unsigned int argY);
		unsigned int GetY();
		void SetWidth(unsigned int argWidth);
		unsigned int SetWidth();
		void SetHeight(unsigned int argHeight);
		unsigned int GetHeight();
		HWND GetHWin();
	};
}

#endif