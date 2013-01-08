#ifndef MOUSE_H_
#define MOUSE_H_
#define DIRECTINPUT_VERSION 0x0800

#include <d3d9.h>
#include <dinput.h>
#include "..\logger\logger.h"
#include "..\window\Win32Window.h"
#include "MouseState.h"

namespace engine
{
	/**
	 * This class is responsible for listening to, and handling of, mouse input.
	 */
	class Mouse
	{
	private:
		std::list<std::string> keymap;
		LPDIRECTINPUTDEVICE8 pDevice;
		MouseState* pState;

		DIPROPDWORD dipdw;
	public:
		Mouse(Window* argPWindow, LPDIRECTINPUT8 argPInput);
		~Mouse();
		void CleanUp();
		
		void RegisterKey(std::string argKey);
		
		bool DoAcquire();
		MouseState* GetState();
		void UpdateState();
	};
}

#endif