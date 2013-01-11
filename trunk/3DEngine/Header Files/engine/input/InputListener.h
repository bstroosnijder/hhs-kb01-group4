#ifndef INPUTLISTENER_H_
#define INPUTLISTENER_H_

#include <string>

namespace engine
{
	class InputListener
	{
	public:
		virtual void InputEvent(std::string argBind, float argSpeed)=0;
	};
}

#endif