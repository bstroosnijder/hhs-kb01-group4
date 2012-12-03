#include "Win32Window.h"

namespace engine
{
	//---Public attributes---
	//---Private attributes---
	//---Public methods---

	/**
	 * Constructor for Win32Window class.
	 */
	Win32Window::Win32Window()
	{
		Win32Window("My First Window", 100, 100, 300, 200);
	}

	/**
	 * Constructor for Win32Window class.
	 * @param		char*	argPTitle is the title for the new window
	 * @param		int		argX is the x-axis position for the new window
	 * @param		int		argY is the y-axis position for the new window
	 * @param		int		argWidth is the width for the new window
	 * @param		int		argHeight is the height for the new window
	 */
	Win32Window::Win32Window(char* argPTitle, int argX, int argY, int argWidth, int argHeight)
	{
		this->title = argPTitle;
		this->x = argX;
		this->y = argY;
		this->width = argWidth;
		this->height = argHeight;

		WNDCLASSEX wc = 
		{
			sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
			GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
			"3DEngine", NULL
		};

		RegisterClassEx(&wc);

		this->hWin = CreateWindow(	"3DEngine", this->title, WS_OVERLAPPEDWINDOW,
									this->x, this->y, this->width, this->height,
									NULL, NULL, wc.hInstance, NULL);

		ShowWindow(this->hWin, SW_SHOWDEFAULT);
		UpdateWindow(this->hWin);
	}

	/**
	 * Destructor for Win32Window class.
	 * @return void
	 */
	Win32Window::~Win32Window()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void Win32Window::CleanUp()
	{
	}

	/**
	 * Listen to what windows tells our window
	 * @param		HWND		The window handle to the window
	 * @param		UINT		halp?
	 * @param		WPARAM		halp?
	 * @param		LPARAM		halp?
	 * @return		LRESULT		halp?
	 */
	LRESULT WINAPI Win32Window::MsgProc(HWND argHWin, UINT argMsg, WPARAM argWParam, LPARAM argLParam)
	{
		switch(argMsg)
		{
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
		}

		return DefWindowProc(argHWin, argMsg, argWParam, argLParam);
	}

	void Win32Window::SetTitle(char* argTitle)
	{
		this->title = argTitle;
	}

	char* Win32Window::GetTitle()
	{
		return this->title;
	}

	void Win32Window::SetX(unsigned int argX)
	{
		this->x = argX;
	}

	unsigned int Win32Window::GetX()
	{
		return this->x;
	}

	void Win32Window::SetY(unsigned int argY)
	{
		this->y = argY;
	}

	unsigned int Win32Window::GetY()
	{
		return this->y;
	}

	void Win32Window::SetWidth(unsigned int argWidth)
	{
		this->width = argWidth;
	}

	unsigned int Win32Window::SetWidth()
	{
		return this->width;
	}

	void Win32Window::SetHeight(unsigned int argHeight)
	{
		this->height = argHeight;
	}

	unsigned int Win32Window::GetHeight()
	{
		return this->height;
	}

	HWND Win32Window::GetHWin()
	{
		return this->hWin;
	}

	//---Private methods---
}