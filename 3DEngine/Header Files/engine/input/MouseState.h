#ifndef MOUSESTATE_H_
#define MOUSESTATE_H_

namespace engine
{
	struct MouseState {
		long MOUSE_X;
		long MOUSE_Y;
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
		bool IsBindActive(std::string argBind)
		{
			if(argBind == "MOUSE_X")
			{
				return true;
			}
			else if(argBind == "MOUSE_Y")
			{
				return true;
			}
			else if(argBind == "KEY_LMB")
			{
				return KEY_LMB;
			}
			else if(argBind == "KEY_RMB")
			{
				return KEY_RMB;
			}
			else if(argBind == "MOUSE_UP")
			{
				return MOUSE_UP > 0;
			}
			else if(argBind == "MOUSE_DOWN")
			{
				return MOUSE_DOWN > 0;
			}
			else if(argBind == "MOUSE_LEFT")
			{
				return MOUSE_LEFT > 0;
			}
			else if(argBind == "MOUSE_RIGHT")
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
			if(argAxis == "MOUSE_X")
			{
				return MOUSE_X;
			}
			else if(argAxis == "MOUSE_Y")
			{
				return MOUSE_Y;
			}
			else if(argAxis == "MOUSE_UP")
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