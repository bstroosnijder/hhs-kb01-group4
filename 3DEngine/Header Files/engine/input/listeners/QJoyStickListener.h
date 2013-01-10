#ifndef QJOYSTICKLISTENER_H_
#define QJOYSTICKLISTENER_H_

#include <map>
#include <string>
#include "..\QJoyStickState.h"

namespace engine
{
	class QJoyStickListener
	{
	public:
		virtual void DoQJoyStickEvent(std::map<std::string, std::string> argBinds, QJoyStickState* argPState)=0;
	};
}

#endif