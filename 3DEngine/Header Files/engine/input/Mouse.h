#ifndef MOUSE_H_
#define MOUSE_H_

#include "..\logger\Logger.h"

namespace engine
{
	/**
	 * This class is responsible for listening to, and handling of, mouse input.
	 * @author Alex Hodes
	 */
	class Mouse
	{
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