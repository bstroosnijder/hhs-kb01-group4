#ifndef MOUSE_H_
#define MOUSE_H_

#include <d3d9.h>
#include <dinput.h>
#include "..\logger\logger.h"
#include "..\window\Win32Window.h"

namespace engine
{
	/**
	 * This class is responsible for listening to, and handling of, mouse input.
	 */
	class Mouse
	{
	private:
		LPDIRECTINPUTDEVICE8 pDevice;
		DIPROPDWORD dipdw;
	public:
		Mouse(Window* argPWindow, LPDIRECTINPUT8 argPInput);
		~Mouse();
		void CleanUp();

		LPDIRECTINPUTDEVICE8 Mouse::GetDevice();

		bool Mouse::InitMouse();
		bool Mouse::DoAcquire();
		//MouseStruct Mouse::GetMouseInput();
		void Mouse::SetMouseBuffer();
		void Mouse::UpdateState();
	};
}

#endif