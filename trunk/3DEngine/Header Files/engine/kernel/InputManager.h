#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#define DIRECTINPUT_VERSION 0x0800
#include <d3d9.h>
#include <dinput.h>
#include <DXGI.h>  
#include "WindowManager.h"
#include "..\scene\entities\camera.h"
#include "..\input\Keyboard.h"

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
		LPDIRECTINPUT8 dInput;
		LPDIRECTINPUTDEVICE8 dDevice;
		Keyboard keyboard;
	public:
		InputManager();
		~InputManager();
		void CleanUp();
		void RegistrateObserver(Camera* argPCamera);
		bool CreateInputDevice();
		void CreateKeyboard(Window* argWindow);
		void InputBeat();
	};
}

#endif