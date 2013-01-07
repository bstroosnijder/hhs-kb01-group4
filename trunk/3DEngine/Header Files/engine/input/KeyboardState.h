#ifndef KEYBOARDSTATE_H_
#define KEYBOARDSTATE_H_

#include <string>

namespace engine
{
	struct KeyboardState
	{
		bool KEY_A;
		bool KEY_D;
		bool KEY_E;
		bool KEY_Q;
		bool KEY_S;
		bool KEY_W;
		bool KEY_DOWN;
		bool KEY_HOME;
		bool KEY_LEFT;
		bool KEY_LSHIFT;
		bool KEY_RIGHT;
		bool KEY_SPACE;
		bool KEY_UP;

		/**
		 * Checks if a key is down based on a string
		 * @param		std::string		The key to check
		 * @return		bool
		 */
		bool IsKeyDown(std::string argKey)
		{
			if(argKey == "KEY_A")
			{
				return KEY_A;
			}
			else if(argKey == "KEY_D")
			{
				return KEY_D;
			}
			else if(argKey == "KEY_E")
			{
				return KEY_E;
			}
			if(argKey == "KEY_Q")
			{
				return KEY_Q;
			}
			else if(argKey == "KEY_S")
			{
				return KEY_S;
			}
			else if(argKey == "KEY_W")
			{
				return KEY_W;
			}
			if(argKey == "KEY_DOWN")
			{
				return KEY_DOWN;
			}
			else if(argKey == "KEY_HOME")
			{
				return KEY_HOME;
			}
			else if(argKey == "KEY_LEFT")
			{
				return KEY_LEFT;
			}
			if(argKey == "KEY_LSHIFT")
			{
				return KEY_LSHIFT;
			}
			else if(argKey == "KEY_RIGHT")
			{
				return KEY_RIGHT;
			}
			else if(argKey == "KEY_SPACE")
			{
				return KEY_SPACE;
			}
			else if(argKey == "KEY_UP")
			{
				return KEY_UP;
			}
			else
			{
				return false;
			}
		}
	};
}

#endif