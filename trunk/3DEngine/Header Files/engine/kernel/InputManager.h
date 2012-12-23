#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_
#define DIRECTINPUT_VERSION 0x0800

#include <d3d9.h>
#include <dinput.h>
#include <DXGI.h>
#include "..\logger\Logger.h"
#include "WindowManager.h"
#include "..\input\Keyboard.h"
#include "..\input\Mouse.h"

namespace engine
{
	/**
	 * This class is responsible for listening to, and handling of, user input.
	 * Any input from the user, such as keyboard and mouse clicks, will be registered, handled and dispatched by this class.
	 * @author Alex Hodes
	 */
	class InputManager
	{
	private:
		LPDIRECTINPUT8 pInput;

		Keyboard* pKeyboard;
		Mouse* pMouse;
	public:
		InputManager();
		~InputManager();
		void CleanUp();

		void SetupDevices(Window* argWindow);

 		// TOOD: needed here?
		void InputBeat();
	};
}

#endif