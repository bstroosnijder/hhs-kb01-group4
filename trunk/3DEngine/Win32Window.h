#ifndef WIN32WINDOW_H_
#define WIN32WINDOW_H_

#include <Windows.h>
#include "Window.h"
#include "WindowManager.h"

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
		Win32Window(char* argPTitle, unsigned int argX, unsigned int argY, unsigned int argWidth, unsigned int argHeight);
		~Win32Window();
		void CleanUp();
		void SetTitle(char* argTitle);
		char* GetTitle();
		void SetX(unsigned int argX);
		unsigned int GetX();
		void SetY(unsigned int argY);
		unsigned int GetY();
		void SetWidth(unsigned int argWidth);
		unsigned int GetWidth();
		void SetHeight(unsigned int argHeight);
		unsigned int GetHeight();
		HWND GetHWin();
	};
}

#endif