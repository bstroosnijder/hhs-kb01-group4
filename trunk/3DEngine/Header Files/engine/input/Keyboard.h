#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <d3d9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <DXGI.h> 
#include "..\logger\logger.h"
#include <stdlib.h>
	
namespace engine
{
	class Keyboard
	/**
	 * This class is responsible for listening to, and handling of, keyboard input.
	 * @author Alex Hodes
	 */
	{
	private:
		LPDIRECTINPUT8 dInput;
		LPDIRECTINPUTDEVICE8 dDevice;
		HWND hwnd;

	public:
		Keyboard::Keyboard();
		Keyboard::Keyboard(HWND argHwnd,LPDIRECTINPUT8 argdInput,LPDIRECTINPUTDEVICE8 argdDevice);
		~Keyboard();
		bool Keyboard::InitKeyboard();
		void Keyboard::SaveReleaseDevice();
		bool Keyboard::DoAcquire();
		bool Keyboard::ProcessKBInput(byte argKeyPressed);
		void SetHWND(); //todo
	};
}
#endif

