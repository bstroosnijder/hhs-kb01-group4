#ifndef MOUSE_H_
#define MOUSE_H_

#include <d3dx9.h>
#include <dinput.h>
#include "..\logger\Logger.h"

namespace engine
{
	/**
	 * This class is responsible for listening to, and handling of, mouse input.
	 */
	class Mouse
	{
	private:
		LPDIRECTINPUTDEVICE8 pDevice;
	public:
		Mouse();//HWND argHwnd );
		~Mouse();
		void CleanUp();

		bool Mouse::InitMouse();
		bool Mouse::DoAcquire();
		//MouseStruct Mouse::GetMouseInput();
		void Mouse::SetMouseBuffer();
	};
}

#endif