#include <Windows.h>
#include "Window.h"

namespace engine
{
	class Win32Window : public Window
	{
	public:
		Win32Window(const unsigned int argWidth, const unsigned int argHeight);
		~Win32Window();

		virtual int Show();
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	private:
		HINSTANCE instance;
		const unsigned int width;
		const unsigned int height;
	};
}