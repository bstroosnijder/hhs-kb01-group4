#ifndef MOUSESTATE_H_
#define MOUSESTATE_H_

namespace engine
{
	struct MouseState {
		bool KEY_LMB;
		bool KEY_RMB;

		long MOUSE_UP;
		long MOUSE_DOWN;
		long MOUSE_LEFT;
		long MOUSE_RIGHT;

		/**
		 * Checks if a key is down based on a string
		 * @param		std::string		The key to check
		 * @return		bool
		 */
		bool IsKeyDown(std::string argKey)
		{
			if(argKey == "KEY_LMB")
			{
				return KEY_LMB;
			}
			else if(argKey == "KEY_RMB")
			{
				return KEY_RMB;
			}
			else if(argKey == "MOUSE_UP")
			{
				return MOUSE_UP > 0;
			}
			else if(argKey == "MOUSE_DOWN")
			{
				return MOUSE_DOWN > 0;
			}
			else if(argKey == "MOUSE_LEFT")
			{
				return MOUSE_LEFT > 0;
			}
			else if(argKey == "MOUSE_RIGHT")
			{
				return MOUSE_RIGHT > 0;
			}
			else
			{
				return false;
			}
		}
		
		long GetMouseSpeed(std::string argAxis)
		{
			if(argAxis == "MOUSE_UP")
			{
				return MOUSE_UP;
			}
			else if(argAxis == "MOUSE_DOWN")
			{
				return MOUSE_DOWN;
			}
			else if(argAxis == "MOUSE_LEFT")
			{
				return MOUSE_LEFT;
			}
			else if(argAxis == "MOUSE_RIGHT")
			{
				return MOUSE_RIGHT;
			}
			else
			{
				return 0;
			}
		}
	};
}

#endif