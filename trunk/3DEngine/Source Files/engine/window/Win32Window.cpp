#include "..\..\..\Header Files\engine\window\Win32Window.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Constructs the Win32Window object.
	 * @param		char*				argPTitle is the title for the new window
	 * @param		unsigned int		argX is the x-axis position for the new window
	 * @param		unsigned int		argY is the y-axis position for the new window
	 * @param		unsigned int		argWidth is the width for the new window
	 * @param		unsigned int		argHeight is the height for the new window
	 */
	Win32Window::Win32Window(std::string argTitle, int argX, int argY, unsigned int argWidth, unsigned int argHeight)
	{
		this->title = argTitle;
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

		this->hWin = CreateWindow(	"3DEngine", this->title.c_str(), WS_OVERLAPPEDWINDOW,
									this->x, this->y, this->width, this->height,
									NULL, NULL, wc.hInstance, NULL);

		ShowWindow(this->hWin, SW_SHOWDEFAULT);
		UpdateWindow(this->hWin);
	}

	/**
	 * Destructs the Win32Window object.
	 * @return		void
	 */
	Win32Window::~Win32Window()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing this object.
	 * @return		void
	 */
	void Win32Window::CleanUp()
	{
	}

	/**
	 * Set the title of this window.
	 * @param		char*				The new title for this window.
	 * @return		void
	 */
	void Win32Window::SetTitle(std::string argPTitle)
	{
		this->title = argPTitle;
	}

	/**
	 * Obtain the title of this Window.
	 * @return		char*
	 */
	std::string Win32Window::GetTitle()
	{
		return this->title;
	}

	/**
	 * Set the X position (relative to the screen) of this Window.
	 * @param		int		The new x position.
	 * @return		void
	 */
	void Win32Window::SetX(int argX)
	{
		this->x = argX;
	}

	/**
	 * Get the X position (relative to the screen) of this Window.
	 * @return		int
	 */
	int Win32Window::GetX()
	{
		return this->x;
	}

	/**
	 * Set the Y position (relative to the screen) of this Window.
	 * @param		int		The new Y position.
	 * @return		void
	 */
	void Win32Window::SetY(int argY)
	{
		this->y = argY;
	}

	/**
	 * Get the Y position (relative to the screen) of this Window.
	 * @return		int
	 */
	int Win32Window::GetY()
	{
		return this->y;
	}

	/**
	 * Set the width of this Window.
	 * @param		unsigned int		The new width of the window.
	 * @return		void
	 */
	void Win32Window::SetWidth(unsigned int argWidth)
	{
		this->width = argWidth;
	}

	/**
	 * Get the width of this Window.
	 * @return		unsigned int
	 */
	unsigned int Win32Window::GetWidth()
	{
		return this->width;
	}

	/**
	 * Set the height of this Window.
	 * @param		unsigned int		The new height of the window
	 * @return		void
	 */
	void Win32Window::SetHeight(unsigned int argHeight)
	{
		this->height = argHeight;
	}

	/**
	 * Get the height of this Window.
	 * @return		unsigned int
	 */
	unsigned int Win32Window::GetHeight()
	{
		return this->height;
	}

	/**
	 * Get the physical WindowHandler of this Window.
	 * @return		HWND
	 */
	HWND Win32Window::GetHWin()
	{
		return this->hWin;
	}
}