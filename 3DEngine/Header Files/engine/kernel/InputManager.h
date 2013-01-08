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
#include "..\input\InputObserver.h"
#include "..\input\Keyboard.h"
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
		std::map<std::string, std::string> keybinds;
		std::map<std::string, std::string> mousekeybinds;

		LPDIRECTINPUT8 pInput;

		Keyboard* pKeyboard;
		Mouse* pMouse;
		MouseState* pMouseState;

		std::list<InputObserver*> pObservers;
		void NotifyObservers();
	public:
		InputManager();
		~InputManager();
		void CleanUp();

		void SetupDevices(Window* argWindow);

		void InputBeat();

		void RegisterKey(std::string argKey, std::string argBind);
		void RegisterMouseKey(std::string argKey, std::string argBind);

		void AddObserver(InputObserver* argPInputObserver);
		void RemoveObserver(InputObserver* argPInputObserver);
	};
}

#endif