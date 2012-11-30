#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_

#include "Win32Window.h"

namespace engine
{
	/**
	 * This class manages all created windows.
	 */
	class WindowManager
	{
	public:
		WindowManager();
		~WindowManager();
		void NewWindow(unsigned int argWidth, unsigned int argHeight);
	};
}

#endif