#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_
#define DIRECTINPUT_VERSION 0x0800

#include <map>
#include <list>
#include <d3d9.h>
#include <dinput.h>
#include <DXGI.h>
#include "..\logger\Logger.h"
#include "WindowManager.h"
#include "..\input\InputDevice.h"
#include "..\input\Keyboard.h"
#include "..\input\Mouse.h"
#include "..\input\JoyStick.h"

namespace engine
{
	/**
	 * This class is responsible for listening to, and handling of, user input.
	 * Any input from the user, such as keyboard and mouse clicks, will be registered, handled and dispatched by this class.
	 */
	class InputManager
	{
	private:
		LPDIRECTINPUT8 pInput;
		static bool HasJoyStick;

		Keyboard* pKeyboard;
		Mouse* pMouse;
		JoyStick* pJoyStick;
	public:
		static const unsigned long KEYBOARD;
		static const unsigned long MOUSE;
		static const unsigned long JOYSTICK;

		InputManager();
		~InputManager();
		void CleanUp();
		static BOOL CALLBACK SetupDeviceCallback(LPCDIDEVICEINSTANCE lpddi, void* pvRef);
		void SetupDevices(Window* argpWindow);

		Keyboard* GetKeyboard();
		Mouse* GetMouse();
		JoyStick* GetJoyStick();

		bool HasDevice(unsigned long argDeviceIndex);
		InputDevice* GetDevice(unsigned long argDeviceIndex);
		void UpdateDevice(unsigned long argDeviceIndex);

		void InputBeat();
	};
}

#endif