#ifndef MOUSE_H_
#define MOUSE_H_
#define DIRECTINPUT_VERSION 0x0800

#include <map>
#include <list>
#include <string>
#include <d3d9.h>
#include <dinput.h>
#include "InputDevice.h"
#include "listeners\MouseListener.h"
#include "..\logger\logger.h"
#include "MouseState.h"
#include "..\window\Win32Window.h"

namespace engine
{
	/**
	 * This class is responsible for listening to, and handling of, mouse input.
	 */
	class Mouse : public InputDevice
	{
	private:
		std::list<MouseListener*> listeners;
		MouseState* pState;

		void NotifyListeners();
		void ResetState();
	public:
		Mouse(Window* argPWindow, LPDIRECTINPUT8 argPInput);
		~Mouse();
		void CleanUp();
		
		void AddListener(MouseListener* argPMouseListener);
		void RemoveListener(MouseListener* argPMouseListener);
		
		void UpdateState();
	};
}

#endif