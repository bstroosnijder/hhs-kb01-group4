#ifndef MOUSELISTENER_H_
#define MOUSELISTENER_H_

#include <map>
#include <string>
#include "..\MouseState.h"

namespace engine
{
	class MouseListener
	{
	public:
		virtual void DoMouseEvent(std::map<std::string, std::string> argBinds, MouseState* argPState)=0;
	};
}

#endif