#ifndef INPUTDEVICE_H_
#define INPUTDEVICE_H_
#define DIRECTINPUT_VERSION 0x0800

#include <map>
#include <list>
#include <string>
#include <d3d9.h>
#include <dinput.h>
#include "InputListener.h"

namespace engine
{
	class InputDevice
	{
	protected:
		LPDIRECTINPUTDEVICE8 pDevice;
		std::map<std::string, std::string> binds;
		std::list<InputListener*> inputListeners;

		void NotifyInputListeners(std::string argBind, float argSpeed);
	public:
		InputDevice();
		
		bool DoAcquire();
		virtual void UpdateState()=0;

		void AddBind(std::string argKey, std::string argBind);

		void AddInputListener(InputListener* argPInputListener);
		void RemoveInputListener(InputListener* argPInputListener);
	};
}

#endif