#ifndef QJOYSTICK_H_
#define QJOYSTICK_H_
#define DIRECTINPUT_VERSION 0x0800

#include <map>
#include <list>
#include <string>
#include <d3d9.h>
#include <dinput.h>
#include "InputDevice.h"
#include "listeners\QJoyStickListener.h"
#include "..\logger\logger.h"
#include "QJoyStickState.h"
#include "..\window\Win32Window.h"

namespace engine
{
	/**
	 * This class is responsible for listening to, and handling of, keyboard input.
	 */
	class QJoyStick : public InputDevice
	{
	private:
		std::list<QJoyStickListener*> listeners;
		QJoyStickState* pState;

		void NotifyListeners();
		void ResetState();
	public:
		QJoyStick(Window* argPWindow, LPDIRECTINPUT8 argPInput);
		~QJoyStick(void);
		void CleanUp();
		
		void AddListener(QJoyStickListener* argPQJoyStickListener);
		void RemoveListener(QJoyStickListener* argPQJoyStickListener);

		void UpdateState();//todo
	};

}	
#endif

