#ifndef QJOYSTICKSTATE_H_
#define QJOYSTICKSTATE_H_

#include <string>

namespace engine
{
	struct QJoyStickState
	{
		bool KEY_1;
		bool KEY_2;
		bool KEY_3;
		bool KEY_4;
		bool KEY_5;
		bool KEY_6;
		bool KEY_7;
		bool KEY_8;
		bool KEY_LEFT;
		bool KEY_DOWN;
		bool KEY_RIGHT;
		bool KEY_UP;
		unsigned long JOY_X;

		/**
		 * Checks if a key is down based on a string
		 * @param		std::string		The key to check
		 * @return		bool
		 */
		bool IsBindActive(std::string argBind)
		{
			if(argBind == "KEY_1")
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
			else if(argBind == "KEY_LEFT")
			{
				return KEY_LEFT;
			}
			else if(argBind == "KEY_DOWN")
			{
				return KEY_DOWN;
			}
			else if(argBind == "KEY_RIGHT")
			{
				return KEY_RIGHT;
			}
			else if(argBind == "KEY_UP")
			{
				return KEY_UP;
			}
			else if(argBind == "JOY_X")
			{
				return true;
			}

			
			else
			{
				return false;
			}
		}
		long GetStickSpeed(std::string argAxis)
		{
			if(argAxis == "JOY_X")
			{
				return JOY_X;
			}
			else
			{
				return 0;
			}
		}
	};
}

#endif