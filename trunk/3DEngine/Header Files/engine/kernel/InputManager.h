#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_
#define DIRECTINPUT_VERSION 0x0800

#include <list>
#include <d3d9.h>
#include <dinput.h>
#include <DXGI.h>
#include "..\logger\Logger.h"
#include "WindowManager.h"
#include "..\input\InputObserver.h"
#include "..\input\Keyboard.h"
#include "..\input\KeyboardState.h"
#include "..\input\Mouse.h"
#include "..\input\MouseState.h"

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

		Keyboard* pKeyboard;
		KeyboardState* pKeyboardState;
		Mouse* pMouse;
		MouseState* pMouseState;

		std::list<InputObserver*> pObservers;
		void NotifyObservers();
	public:
		InputManager();
		~InputManager();
		void CleanUp();

		void SetupDevices(Window* argWindow);

 		// TOOD: needed here?
		void InputBeat();

		void AddObserver(InputObserver* argPInputObserver);
		void RemoveObserver(InputObserver* argPInputObserver);
	};
}

#endif