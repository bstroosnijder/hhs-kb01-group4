#ifndef INPUTDEVICE_H_
#define INPUTDEVICE_H_
#define DIRECTINPUT_VERSION 0x0800

#include <map>
#include <string>
#include <d3d9.h>
#include <dinput.h>

namespace engine
{
	class InputDevice
	{
	protected:
		std::map<std::string, std::string> binds;
		LPDIRECTINPUTDEVICE8 pDevice;
	public:
		InputDevice();

		void AddBind(std::string argKey, std::string argBind);
		
		bool DoAcquire();
		virtual void UpdateState()=0;
	};
}

#endif