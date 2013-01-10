#include "..\..\..\Header Files\engine\input\JoyStick.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---

	/**
	 * Notifies all the listener
	 * @return		void
	 */
	void JoyStick::NotifyListeners()
	{
		std::list<JoyStickListener*>::iterator listenerIt;
		for(listenerIt = this->listeners.begin(); listenerIt != this->listeners.end(); listenerIt++)
		{
			JoyStickListener* pJoyStickListener = *listenerIt;
			pJoyStickListener->DoJoyStickEvent(this->binds, this->pState);
		}
	}

	/**
	 * Reset the state of the qjoystick
	 * @return		void
	 */
	void JoyStick::ResetState()
	{
		this->pState->LSTICK_X		= 0;
		this->pState->LSTICK_Y		= 0;
		this->pState->RSTICK_X		= 0;
		this->pState->RSTICK_Y		= 0;
		this->pState->KEY_1			= false;
		this->pState->KEY_2			= false;
		this->pState->KEY_3			= false;
		this->pState->KEY_4			= false;
		this->pState->KEY_5			= false;
		this->pState->KEY_6			= false;
		this->pState->KEY_7			= false;
		this->pState->KEY_8			= false;
		this->pState->KEY_UP		= false;
		this->pState->KEY_DOWN		= false;
		this->pState->KEY_LEFT		= false;
		this->pState->KEY_RIGHT		= false;
	}

	JoyStick::JoyStick(Window* argPWindow, LPDIRECTINPUT8 argPInput)
	{
		Logger::Log("JoyStick: Creating", Logger::INFO, __FILE__, __LINE__);
		this->listeners = std::list<JoyStickListener*>();
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
		
		// Init the keyboard state
		this->pState = new JoyStickState();
		this->ResetState();

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

	void JoyStick::AddListener(JoyStickListener* argPJoyStickListener)
	{
		this->listeners.push_back(argPJoyStickListener);
	}

	void JoyStick::RemoveListener(JoyStickListener* argPJoyStickListener)
	{
		this->listeners.remove(argPJoyStickListener);
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

				if(key == "LSTICK_X")
				{
					this->pState->LSTICK_X = (long)jState.lX;
				}
				else if(key == "LSTICK_Y")
				{
					this->pState->LSTICK_Y = jState.lY;
				}
				else if(key == "RSTICK_X")
				{
					// TODO
				}
				else if(key == "RSTICK_Y")
				{
					// TODO
				}
				else if(key == "KEY_1")
				{
					this->pState->KEY_1 = (bool)((jState.rgbButtons[0] & 0x80) != 0);
				}
				else if(key == "KEY_2")
				{
					this->pState->KEY_2 = (bool)((jState.rgbButtons[1] & 0x80) != 0);
				}
				else if(key == "KEY_3")
				{
					this->pState->KEY_3 = (bool)((jState.rgbButtons[2] & 0x80) != 0);
				}
				else if(key == "KEY_4")
				{
					this->pState->KEY_4 = (bool)((jState.rgbButtons[3] & 0x80) != 0);
				}
				else if(key == "KEY_5")
				{
					this->pState->KEY_5 = (bool)((jState.rgbButtons[4] & 0x80) != 0);
				}
				else if(key == "KEY_6")
				{
					this->pState->KEY_6 = (bool)((jState.rgbButtons[5] & 0x80) != 0);
				}
				else if(key == "KEY_7")
				{
					this->pState->KEY_7 = (bool)((jState.rgbButtons[6] & 0x80) != 0);
				}
				else if(key == "KEY_8")
				{
					this->pState->KEY_8 = (bool)((jState.rgbButtons[7] & 0x80) != 0);
				}
				else if(key == "KEY_UP")
				{
					// TODO
				}
				else if(key == "KEY_DOWN")
				{
					// TODO
				}
				else if(key == "KEY_LEFT")
				{
					// TODO
				}
				else if(key == "KEY_RIGHT")
				{
					// TODO
				}

				std::stringstream ss;
				ss << "JOYSTICK INPUT" << std::endl;
				ss << "LSTICK_X: " << this->pState->LSTICK_X << std::endl;
				ss << "LSTICK_Y: " << this->pState->LSTICK_Y << std::endl;
				//Logger::Log(ss.str(), 0, 0, 0);
			}

			// Tell our fans
			//this->NotifyListeners();
		}
	}
}