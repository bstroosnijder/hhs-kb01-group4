#ifndef MOUSE_H_
#define MOUSE_H_
#define DIRECTINPUT_VERSION 0x0800

#include <map>
#include <list>
#include <string>
#include <d3d9.h>
#include <dinput.h>
#include "InputDevice.h"
#include "..\logger\logger.h"
#include "..\window\Win32Window.h"

namespace engine
{
	/**
	 * This class is responsible for listening to, and handling of, mouse input.
	 */
	class Mouse : public InputDevice
	{
	public:
		Mouse(Window* argPWindow, LPDIRECTINPUT8 argPInput);
		~Mouse();
		void CleanUp();
		
		void UpdateState();
	};
}

#endif