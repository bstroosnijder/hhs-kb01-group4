#include "..\..\..\Header Files\engine\input\JoyStick.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

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
	
	
	engine::JoyStick::~JoyStick()
	{
		Logger::Log("JoyStick: Disposing", Logger::INFO, __FILE__, __LINE__);
		this->CleanUp();
	}

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
				std::string key		= bindsIt->first;
				std::string bind	= bindsIt->second;
				float speed			= 1.0f;

				if(	(key == "KEY_1" && (bool)((jState.rgbButtons[0] & 0x80) != 0)) ||
					(key == "KEY_2" && (bool)((jState.rgbButtons[1] & 0x80) != 0)) ||
					(key == "KEY_3" && (bool)((jState.rgbButtons[2] & 0x80) != 0)) ||
					(key == "KEY_4" && (bool)((jState.rgbButtons[3] & 0x80) != 0)) ||
					(key == "KEY_5" && (bool)((jState.rgbButtons[4] & 0x80) != 0)) ||
					(key == "KEY_6" && (bool)((jState.rgbButtons[5] & 0x80) != 0)) ||
					(key == "KEY_7" && (bool)((jState.rgbButtons[6] & 0x80) != 0)) ||
					(key == "KEY_8" && (bool)((jState.rgbButtons[7] & 0x80) != 0)) ||
					(key == "KEY_UP" && false) ||
					(key == "KEY_DOWN" && false) ||
					(key == "KEY_LEFT" && false) ||
					(key == "KEY_RIGHT" && false))
				{
					// Tell our fans
					this->NotifyInputListeners(bind, speed);
				}
				else if(key == "LSTICK_X" && ((jState.lX <= (SHRT_MAX - optSmoothness)) || (jState.lX >= (SHRT_MAX + optSmoothness))))
				{
					float stickPos = (float)jState.lX - SHRT_MAX;
					speed = (stickPos / optSmoothness) * optSensitivity;

					// Tell our fans
					this->NotifyInputListeners(bind, speed*2);
				}
				else if(key == "LSTICK_Y" && ((jState.lY <= (SHRT_MAX - optSmoothness)) || (jState.lY >= (SHRT_MAX + optSmoothness))))
				{
					float stickPos = (float)jState.lY - SHRT_MAX;
					speed = (stickPos / optSmoothness) * optSensitivity;

					// Tell our fans
					this->NotifyInputListeners(bind, speed*2);
				}
				else if(key == "RSTICK_X" && jState.lRx == 0 && ((jState.lZ <= (SHRT_MAX - optSmoothness)) || (jState.lZ >= (SHRT_MAX + optSmoothness))))
				{
					float stickPos = (float)jState.lZ - SHRT_MAX;
					speed = (stickPos / optSmoothness) * optSensitivity;

					// Tell our fans
					this->NotifyInputListeners(bind, speed);
				}
				else if(key == "RSTICK_X" && ((jState.lRx <= (SHRT_MAX - optSmoothness)) || (jState.lRx >= (SHRT_MAX + optSmoothness))))
				{
					float stickPos = (float)jState.lRx - SHRT_MAX;
					speed = (stickPos / optSmoothness) * optSensitivity;

					// Tell our fans
					this->NotifyInputListeners(bind, speed);
				}
				else if(key == "RSTICK_Y" && jState.lRy == 0 && ((jState.lRz <= (SHRT_MAX - optSmoothness)) || (jState.lRz >= (SHRT_MAX + optSmoothness))))
				{
					float stickPos = (float)jState.lRz - SHRT_MAX;
					speed = (stickPos / optSmoothness) * optSensitivity;

					// Tell our fans
					this->NotifyInputListeners(bind, speed);
				}
				else if(key == "RSTICK_Y" && ((jState.lRy <= (SHRT_MAX - optSmoothness)) || (jState.lRy >= (SHRT_MAX + optSmoothness))))
				{
					float stickPos = (float)jState.lRy - SHRT_MAX;
					speed = (stickPos / optSmoothness) * optSensitivity;

					// Tell our fans
					this->NotifyInputListeners(bind, speed);
				}
			}

			std::stringstream ss;

			ss << "--- JOYSTICK STATE ---" << std::endl;
			ss << "LSTICK_RX:\t" << jState.lRx << std::endl;


			//Logger::Log(ss.str(), Logger::INFO, __FILE__, __LINE__);
		}
	}
}