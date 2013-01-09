#ifndef KEYBOARDLISTENER_H_
#define KEYBOARDLISTENER_H_

#include <map>
#include <string>
#include "..\KeyboardState.h"

namespace engine
{
	class KeyboardListener
	{
	public:
		virtual void DoKeyboardEvent(std::map<std::string, std::string> argBinds, KeyboardState* argPState)=0;
	};
}

#endif