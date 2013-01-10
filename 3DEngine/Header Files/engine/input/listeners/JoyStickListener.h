#ifndef JOYSTICKLISTENER_H_
#define JOYSTICKLISTENER_H_

#include <map>
#include <string>
#include "..\JoyStickState.h"

namespace engine
{
	class JoyStickListener
	{
	public:
		virtual void DoJoyStickEvent(std::map<std::string, std::string> argBinds, JoyStickState* argPState)=0;
	};
}

#endif