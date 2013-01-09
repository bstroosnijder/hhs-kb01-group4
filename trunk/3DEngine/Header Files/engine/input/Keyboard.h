#ifndef KEYBOARD_H_
#define KEYBOARD_H_
#define DIRECTINPUT_VERSION 0x0800

#include <map>
#include <list>
#include <string>
#include <d3d9.h>
#include <dinput.h>
#include "InputDevice.h"
#include "listeners\KeyboardListener.h"
#include "..\logger\logger.h"
#include "KeyboardState.h"
#include "..\window\Win32Window.h"
	
namespace engine
{
	/**
	 * This class is responsible for listening to, and handling of, keyboard input.
	 */
	class Keyboard : public InputDevice
	{
	private:
		std::list<KeyboardListener*> listeners;
		KeyboardState* pState;

		void NotifyListeners();
		void ResetState();
	public:
		Keyboard(Window* argPWindow, LPDIRECTINPUT8 argPInput);
		~Keyboard();
		void CleanUp();
		
		void AddListener(KeyboardListener* argPKeyboardListener);
		void RemoveListener(KeyboardListener* argPKeyboardListener);

		void UpdateState();
	};
}

#endif