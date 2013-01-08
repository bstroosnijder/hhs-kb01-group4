#ifndef INPUTOBSERVER_H_
#define INPUTOBSERVER_H_

#include <map>
#include <string>
#include "..\logger\Logger.h"
#include "MouseState.h"
#include "KeyboardState.h"

namespace engine
{
	class InputObserver
	{
	public:
		virtual void Notify(std::map<std::string, std::string> argKeybinds, KeyboardState* argPKeyboardState,
							std::map<std::string, std::string> argMouseKeybinds, MouseState* argPMouseState)=0;
	};
}

#endif