#ifndef KEYBOARD_H_
#define KEYBOARD_H_
#define DIRECTINPUT_VERSION 0x0800

#include <list>
#include <string>
#include <d3d9.h>
#include <dinput.h>
#include "..\logger\logger.h"
#include "KeyboardState.h"
#include "..\window\Win32Window.h"
	
namespace engine
{
	/**
	 * This class is responsible for listening to, and handling of, keyboard input.
	 */
	class Keyboard
	{
	private:
		std::list<std::string> keymap;
		LPDIRECTINPUTDEVICE8 pDevice;
		KeyboardState* pState;
	public:
		Keyboard(Window* argPWindow, LPDIRECTINPUT8 argPInput);
		~Keyboard();
		void CleanUp();

		void RegisterKey(std::string argKey);

		bool DoAcquire();
		KeyboardState* GetState();
		void UpdateState();
	};
}

#endif