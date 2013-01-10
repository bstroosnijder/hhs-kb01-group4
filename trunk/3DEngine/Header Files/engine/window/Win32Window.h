#ifndef WIN32WINDOW_H_
#define WIN32WINDOW_H_

#include <Windows.h>
#include "Window.h"
#include "..\logger\Logger.h"
#include "..\kernel\WindowManager.h"

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
		Win32Window(std::string argTitle, int argX, int argY, unsigned int argWidth, unsigned int argHeight);
		~Win32Window();
		void CleanUp();
		void SetTitle(std::string argTitle);
		std::string GetTitle();
		void SetX(int argX);
		int GetX();
		void SetY(int argY);
		int GetY();
		void SetWidth(unsigned int argWidth);
		unsigned int GetWidth();
		void SetHeight(unsigned int argHeight);
		unsigned int GetHeight();
		HWND GetHWin();
	};
}

#endif