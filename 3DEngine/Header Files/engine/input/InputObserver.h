#ifndef INPUTOBSERVER_H_
#define INPUTOBSERVER_H_

#include "..\logger\Logger.h"
#include "KeyboardState.h"

namespace engine
{
	class InputObserver
	{
	public:
		virtual void Notify(KeyboardState* argPKeyboardState)=0;
	};
}

#endif