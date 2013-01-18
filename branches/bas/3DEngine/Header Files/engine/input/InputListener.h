#ifndef INPUTLISTENER_H_
#define INPUTLISTENER_H_

#include <string>

namespace engine
{
	/**
	 * This interface forces the classes that implement it to implement an InputEvent method.
	 * Due to this, it generalizes the classes that listen for input.s	
	 */
	class InputListener
	{
	public:
		virtual void InputEvent(std::string argBind, float argSpeed)=0;
	};
}

#endif