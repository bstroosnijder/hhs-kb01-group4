#ifndef JOYSTICKSTATE_H_
#define JOYSTICKSTATE_H_

#include <string>

namespace engine
{
	struct JoyStickState
	{
		long LSTICK_X;
		long LSTICK_Y;
		long RSTICK_X;
		long RSTICK_Y;
		bool KEY_1;
		bool KEY_2;
		bool KEY_3;
		bool KEY_4;
		bool KEY_5;
		bool KEY_6;
		bool KEY_7;
		bool KEY_8;
		bool KEY_UP;
		bool KEY_DOWN;
		bool KEY_LEFT;
		bool KEY_RIGHT;

		/**
		 * Checks if a key is down based on a string
		 * @param		std::string		The key to check
		 * @return		bool
		 */
		bool IsBindActive(std::string argBind)
		{
			if(argBind == "LSTICK_X")
			{
				return true;
			}
			else if(argBind == "LSTICK_Y")
			{
				return true;
			}
			else if(argBind == "RSTICK_X")
			{
				return true;
			}
			else if(argBind == "RSTICK_Y")
			{
				return true;
			}
			else if(argBind == "KEY_1")
			{
				return KEY_1;
			}
			else if(argBind == "KEY_2")
			{
				return KEY_2;
			}
			else if(argBind == "KEY_3")
			{
				return KEY_3;
			}
			else if(argBind == "KEY_4")
			{
				return KEY_4;
			}
			else if(argBind == "KEY_5")
			{
				return KEY_5;
			}
			else if(argBind == "KEY_6")
			{
				return KEY_6;
			}
			else if(argBind == "KEY_7")
			{
				return KEY_7;
			}
			else if(argBind == "KEY_8")
			{
				return KEY_8;
			}
			else if(argBind == "KEY_UP")
			{
				return KEY_UP;
			}
			else if(argBind == "KEY_DOWN")
			{
				return KEY_DOWN;
			}
			else if(argBind == "KEY_LEFT")
			{
				return KEY_LEFT;
			}
			else if(argBind == "KEY_RIGHT")
			{
				return KEY_RIGHT;
			}
			else
			{
				return false;
			}
		}

		long GetStickSpeed(std::string argAxis)
		{
			if(argAxis == "LSTICK_X")
			{
				return LSTICK_X;
			}
			else if(argAxis == "LSTICK_Y")
			{
				return LSTICK_Y;
			}
			else if(argAxis == "RSTICK_X")
			{
				return RSTICK_X;
			}
			else if(argAxis == "RSTICK_Y")
			{
				return RSTICK_Y;
			}
			else
			{
				return 0;
			}
		}
	};
}

#endif