#include <Windows.h>
#include "Window.h"

namespace engine
{
	/**
	 * This class creates a window specificly for the Windows Operating System and implements the Window interface.
	 */
	class Win32Window : public Window
	{
	public:
		Win32Window(const unsigned int argWidth, const unsigned int argHeight);
		~Win32Window();
		virtual int Show();
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	private:
		HINSTANCE instance;
		unsigned int width;
		unsigned int height;
	};
}