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
		propRange.diph.dwSize       = sizeof(DIPROPRANGE); 
		propRange.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
		propRange.diph.dwHow        = DIPH_BYID; 
		propRange.diph.dwObj        = 0;
		propRange.lMin              = -1000; 
		propRange.lMax              = +1000; 
		pDevice->SetProperty(DIPROP_RANGE, &propRange.diph);

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
				else if(key == "LSTICK_X" && (bool)(jState.lX != 0))
				{
					speed = (jState.lX * 0.5f);
					// Tell our fans
					this->NotifyInputListeners(bind, speed);
				}
				else if(key == "LSTICK_Y" && (bool)(jState.lY != 0))
				{
					speed = (jState.lX * 0.5f);
					// Tell our fans
					this->NotifyInputListeners(bind, speed);
				}
				else if(key == "RSTICK_X" && false)
				{
					// Tell our fans
					this->NotifyInputListeners(bind, speed);
				}
				else if(key == "RSTICK_Y" && false)
				{
					// Tell our fans
					this->NotifyInputListeners(bind, speed);
				}
			}
		}
	}
}