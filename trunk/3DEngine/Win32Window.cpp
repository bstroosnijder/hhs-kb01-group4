#include "Win32Window.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---

	/**
	 * stuff
	 * @param		char*				The title of the window
	 * @param		int					The x position of the window
	 * @param		int					The y position of the window
	 * @param		int					The width of the window
	 * @param		int					The height of the window
	 * @return		void
	 */
	void Win32Window::Init(char* argPTitle, int argX, int argY, int argWidth, int argHeight)
	{
		this->title = argPTitle;
		this->x = argX;
		this->y = argY;
		this->width = argWidth;
		this->height = argHeight;

		WNDCLASSEX wc = 
		{
			sizeof(WNDCLASSEX), CS_CLASSDC, WindowManager::MsgProc, 0L, 0L,
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

	//---Public methods---

	/**
	 * Constructor for Win32Window class.
	 */
	Win32Window::Win32Window()
	{
		Init("My First Window", 100, 100, 300, 200);
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
		Init(argPTitle, argX, argY, argWidth, argHeight);
	}

	/**
	 * Destructor for Win32Window class.
	 * @return		void
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
	 * Setter for the title
	 * @param		char*				The new title
	 * @return		void
	 */
	void Win32Window::SetTitle(char* argTitle)
	{
		this->title = argTitle;
	}

	/**
	 * Getter for the title
	 * @return		char*
	 */
	char* Win32Window::GetTitle()
	{
		return this->title;
	}

	/**
	 * Setter for the x position
	 * @param		unsigned int		The new x position
	 * @return		void
	 */
	void Win32Window::SetX(unsigned int argX)
	{
		this->x = argX;
	}

	/**
	 * Getter for the x position
	 * @return		unsigned int
	 */
	unsigned int Win32Window::GetX()
	{
		return this->x;
	}

	/**
	 * Setter for the y position
	 * @param		unsigned int		The new y position
	 * @return		void
	 */
	void Win32Window::SetY(unsigned int argY)
	{
		this->y = argY;
	}

	/**
	 * Getter for the y position
	 * @return		unsigned int
	 */
	unsigned int Win32Window::GetY()
	{
		return this->y;
	}

	/**
	 * Setter for the width of the window
	 * @param		unsigned int		The new width of the window
	 * @return		void
	 */
	void Win32Window::SetWidth(unsigned int argWidth)
	{
		this->width = argWidth;
	}

	/**
	 * Getter for the width of the window
	 * @return		unsigned int
	 */
	unsigned int Win32Window::GetWidth()
	{
		return this->width;
	}

	/**
	 * Setter for the height of the window
	 * @param		unsigned int		The new height of the window
	 * @return		void
	 */
	void Win32Window::SetHeight(unsigned int argHeight)
	{
		this->height = argHeight;
	}

	/**
	 * Getter for the height of the window
	 * @return		unsigned int
	 */
	unsigned int Win32Window::GetHeight()
	{
		return this->height;
	}

	/**
	 * Getter for the window handle of the window
	 * @return		HWND
	 */
	HWND Win32Window::GetHWin()
	{
		return this->hWin;
	}
}