#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

namespace engine
{
	/**
	 * This class is responsible for listening to, and handling of, user input.
	 * Any input from the user, such as keyboard and mouse clicks, will be registered, handled and dispatched by this class.
	 */
	class InputManager
	{
	public:
		InputManager();
		~InputManager();
		void CleanUp();
	};
}

#endif