#include "..\..\..\Header Files\engine\input\JoyStick.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Constructs the Joystick object.
	 * @param		Window*					The Window on which this Joystick should listen. This is needed to obtain the HWND object.
	 * @param		LPDIRECTINPUT8			The Direct8Input* object, needed to allow Direct3D to perform it's magic!
	 */
	JoyStick::JoyStick(Window* argPWindow, LPDIRECTINPUT8 argPInput)
	{
		Logger::Log("JoyStick: Creating", Logger::INFO, __FILE__, __LINE__);
		Win32Window* pWindow = (Win32Window*)argPWindow;

		DIDEVCAPS caps;
		caps.dwSize=sizeof(DIDEVCAPS);

		argPInput->CreateDevice(GUID_Joystick, &this->pDevice, NULL);
		this->pDevice->SetDataFormat(&c_dfDIJoystick);
		this->pDevice->SetCooperativeLevel(pWindow->GetHWin(),DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		this->pDevice->GetCapabilities(&caps);

		DIPROPRANGE propRange; 
		propRange.diph.dwSize			= sizeof(DIPROPRANGE); 
		propRange.diph.dwHeaderSize		= sizeof(DIPROPHEADER); 
		propRange.diph.dwHow			= DIPH_BYID; 
		propRange.diph.dwObj			= 0;
		propRange.lMin					= -1000; 
		propRange.lMax					= +1000; 
		pDevice->SetProperty(DIPROP_RANGE, &propRange.diph);

		// Set default options
		this->options["sensitivity"]	= "0.05";
		this->options["smoothness"]		= "8000";

		Logger::Log("JoyStick: Finished", Logger::INFO, __FILE__, __LINE__);
	}
	
	/**
	 * Destructs the Joystick object.
	 */
	engine::JoyStick::~JoyStick()
	{
		Logger::Log("JoyStick: Disposing", Logger::INFO, __FILE__, __LINE__);
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void JoyStick::CleanUp()
	{
		if (this->pDevice != NULL)
		{
			this->pDevice->Unacquire();
			this->pDevice->Release();
		}
	}

	/**
	 * Updates the keyboard state
	 * @return		void
	 */
	void JoyStick::UpdateState()
	{
		if(!SUCCEEDED(this->pDevice->Poll())) 
		{			
			this->DoAcquire();
		}
		else
		{
			DIJOYSTATE jState;
			this->pDevice->GetDeviceState(sizeof(DIJOYSTATE), (LPVOID)&jState);

			// Get options
			float optSensitivity		= (float)std::atof(this->options["sensitivity"].c_str());
			float optSmoothness			= (float)std::atof(this->options["smoothness"].c_str());
			
			std::map<std::string, std::string>::iterator bindsIt;
			for(bindsIt = this->binds.begin(); bindsIt != this->binds.end(); bindsIt++)
			{
				int doNotify					= 0;
				std::vector<std::string> keys	= explode(':', bindsIt->first);
				std::string bind				= bindsIt->second;
				float speed						= 1.0f;

				std::vector<std::string>::iterator keysIt;
				for(keysIt = keys.begin(); keysIt != keys.end(); keysIt++)
				{
					std::string key = *keysIt;

					if(	(key == "KEY_1"				&& ((jState.rgbButtons[0] & 0x80) != 0)) ||
						(key == "KEY_2"				&& ((jState.rgbButtons[1] & 0x80) != 0)) ||
						(key == "KEY_3"				&& ((jState.rgbButtons[2] & 0x80) != 0)) ||
						(key == "KEY_4"				&& ((jState.rgbButtons[3] & 0x80) != 0)) ||
						(key == "KEY_5"				&& ((jState.rgbButtons[4] & 0x80) != 0)) ||
						(key == "KEY_6"				&& ((jState.rgbButtons[5] & 0x80) != 0)) ||
						(key == "KEY_7"				&& ((jState.rgbButtons[6] & 0x80) != 0)) ||
						(key == "KEY_8"				&& ((jState.rgbButtons[7] & 0x80) != 0)) ||
						(key == "KEY_UP"			&& (jState.rgdwPOV[0] == 0)) ||
						(key == "KEY_DOWN"			&& (jState.rgdwPOV[0] == 18000)) ||
						(key == "KEY_LEFT"			&& (jState.rgdwPOV[0] == 27000)) ||
						(key == "KEY_RIGHT"			&& (jState.rgdwPOV[0] == 9000)) ||
						(key == "KEY_UP_LEFT"		&& (jState.rgdwPOV[0] == 31500)) ||
						(key == "KEY_UP_RIGHT"		&& (jState.rgdwPOV[0] == 4500)) ||
						(key == "KEY_DOWN_LEFT"		&& (jState.rgdwPOV[0] == 22500)) ||
						(key == "KEY_DOWN_RIGHT"	&& (jState.rgdwPOV[0] == 13500)))
					{
						doNotify++;
					}
					else if(key == "LSTICK_X" && ((jState.lX <= (SHRT_MAX - optSmoothness)) || (jState.lX >= (SHRT_MAX + optSmoothness))))
					{
						float stickPos = (float)jState.lX - SHRT_MAX;
						speed = (stickPos / optSmoothness) * optSensitivity;
						doNotify++;
					}
					else if(key == "LSTICK_Y" && ((jState.lY <= (SHRT_MAX - optSmoothness)) || (jState.lY >= (SHRT_MAX + optSmoothness))))
					{
						float stickPos = (float)jState.lY - SHRT_MAX;
						speed = (stickPos / optSmoothness) * optSensitivity;
						doNotify++;
					}
					else if(key == "RSTICK_X" && ((jState.lRx <= (SHRT_MAX - optSmoothness)) || (jState.lRx >= (SHRT_MAX + optSmoothness))))
					{
						float stickPos = (float)jState.lRx - SHRT_MAX;
						speed = (stickPos / optSmoothness) * optSensitivity;
						doNotify++;
					}
					else if(key == "RSTICK_Y" && ((jState.lRy <= (SHRT_MAX - optSmoothness)) || (jState.lRy >= (SHRT_MAX + optSmoothness))))
					{
						float stickPos = (float)jState.lRy - SHRT_MAX;
						speed = (stickPos / optSmoothness) * optSensitivity;
						doNotify++;
					}
					else if((key == "LTRIGGER"	&& (jState.lZ >= (SHRT_MAX + optSmoothness))) ||
							(key == "RTRIGGER"	&& (jState.lZ <= (SHRT_MAX - optSmoothness))))
					{
						float triggerPos = (float)jState.lZ - SHRT_MAX;
						speed = (triggerPos / optSmoothness) * optSensitivity;
						doNotify++;
					}
				}
				
				if(doNotify == keys.size())
				{
					// Tell our fans
					this->NotifyInputListeners(bind, speed);
				}
			}
		}
	}
}