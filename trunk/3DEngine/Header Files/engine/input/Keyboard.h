#ifndef KEYBOARD_H_
#define KEYBOARD_H_
#define DIRECTINPUT_VERSION 0x0800

#include <d3d9.h>
#include <dinput.h>
#include "..\logger\logger.h"
#include "..\window\Win32Window.h"
	
namespace engine
{
	/**
	 * This class is responsible for listening to, and handling of, keyboard input.
	 */
	class Keyboard
	{
	private:
		LPDIRECTINPUTDEVICE8 pDevice;
	public:
		Keyboard::Keyboard(Window* argPWindow, LPDIRECTINPUT8 argPInput);
		~Keyboard();
		void CleanUp();

		bool Keyboard::DoAcquire();
		bool Keyboard::ProcessKBInput(byte argKeyPressed);
	};
}

#endif