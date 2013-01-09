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
		bool IsBindActive(std::string argBind)
		{
			if(argBind == "KEY_A")
			{
				return KEY_A;
			}
			else if(argBind == "KEY_D")
			{
				return KEY_D;
			}
			else if(argBind == "KEY_E")
			{
				return KEY_E;
			}
			else if(argBind == "KEY_Q")
			{
				return KEY_Q;
			}
			else if(argBind == "KEY_S")
			{
				return KEY_S;
			}
			else if(argBind == "KEY_W")
			{
				return KEY_W;
			}
			else if(argBind == "KEY_DOWN")
			{
				return KEY_DOWN;
			}
			else if(argBind == "KEY_HOME")
			{
				return KEY_HOME;
			}
			else if(argBind == "KEY_LEFT")
			{
				return KEY_LEFT;
			}
			else if(argBind == "KEY_LSHIFT")
			{
				return KEY_LSHIFT;
			}
			else if(argBind == "KEY_RIGHT")
			{
				return KEY_RIGHT;
			}
			else if(argBind == "KEY_SPACE")
			{
				return KEY_SPACE;
			}
			else if(argBind == "KEY_UP")
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