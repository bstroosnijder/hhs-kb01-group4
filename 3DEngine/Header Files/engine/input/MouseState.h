#ifndef MOUSESTATE_H_
#define MOUSESTATE_H_

namespace engine
{
	struct MouseState {
		bool MOUSE_LEFT;
		bool MOUSE_RIGHT;
		bool MOUSE_UP;
		bool MOUSE_DOWN;
		bool KEY_LMB;
		bool KEY_RMB;

		/**
		 * Checks if a key is down based on a string
		 * @param		std::string		The key to check
		 * @return		bool
		 */
		bool IsKeyDown(std::string argKey)
		{
			if(argKey == "MOUSE_LEFT")
			{
				return MOUSE_LEFT;
			}
			else if(argKey == "MOUSE_RIGHT")
			{
				return MOUSE_RIGHT;
			}
			else if(argKey == "MOUSE_UP")
			{
				return MOUSE_UP;
			}
			if(argKey == "MOUSE_DOWN")
			{
				return MOUSE_DOWN;
			}
			else if(argKey == "KEY_LMB")
			{
				return KEY_LMB;
			}
			else if(argKey == "KEY_RMB")
			{
				return KEY_RMB;
			}
			else
			{
				return false;
			}
		}
	};
}

#endif