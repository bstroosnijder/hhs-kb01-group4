#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <d3d9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>//include kan foutief zijn. Wij hebben niet de juiste includes opgeschreven
#include <DXGI.h>  //''
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
		Keyboard();//TODO
		~Keyboard();//TODO
		Keyboard::Keyboard(HWND argHwnd);
		Keyboard::Keyboard(HWND argHwnd,LPVOID argdInput,LPVOID argdDevice);//TODO HWND needed to set coop level within the initkeyB
		bool Keyboard::InitKeyboard(); //TODO
		void Keyboard::SaveReleaseDevice();//TODO 
		bool Keyboard::DoAcquire();//todo
		void Keyboard::SetHWND(HWND argHWND);//todo
		bool Keyboard::ProcessKBInput(byte argKeyPressed);//todo 
	};
}
#endif

