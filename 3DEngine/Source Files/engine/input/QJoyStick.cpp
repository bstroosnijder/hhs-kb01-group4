#include "..\..\..\Header Files\engine\input\QJoyStick.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---

	/**
	 * Notifies all the listener
	 * @return		void
	 */
	void QJoyStick::NotifyListeners()
	{
		std::list<QJoyStickListener*>::iterator listenerIt;
		for(listenerIt = this->listeners.begin(); listenerIt != this->listeners.end(); listenerIt++)
		{
			QJoyStickListener* pQJoyStickListener = *listenerIt;
			pQJoyStickListener->DoQJoyStickEvent(this->binds, this->pState);
		}
	}

	/**
	 * Reset the state of the qjoystick
	 * @return		void
	 */
	void QJoyStick::ResetState()
	{
		this->pState->KEY_1			= false;
		this->pState->KEY_2			= false;
		this->pState->KEY_3			= false;
		this->pState->KEY_4			= false;
		this->pState->KEY_5			= false;
		this->pState->KEY_6			= false;
		this->pState->KEY_7			= false;
		this->pState->KEY_8			= false;
		this->pState->KEY_LEFT		= false;
		this->pState->KEY_DOWN		= false;
		this->pState->KEY_RIGHT		= false;
		this->pState->KEY_UP		= false;
	}

	engine::QJoyStick::QJoyStick(Window* argPWindow, LPDIRECTINPUT8 argPInput)
	{
		Logger::Log("QJoyStick: Creating", Logger::INFO, __FILE__, __LINE__);
		this->listeners = std::list<QJoyStickListener*>();
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
		this->pState = new QJoyStickState();
		this->ResetState();

		Logger::Log("QJoyStick: Finished", Logger::INFO, __FILE__, __LINE__);
	}
	
	
	engine::QJoyStick::~QJoyStick()
	{
	}

	void QJoyStick::CleanUp()
	{
		if (this->pDevice != NULL)
		{
			this->pDevice->Unacquire();
			this->pDevice->Release();
			delete this->pDevice;
		}
	}

	void QJoyStick::AddListener(QJoyStickListener* argPQJoyStickListener)
	{
		this->listeners.push_back(argPQJoyStickListener);
	}

	void QJoyStick::RemoveListener(QJoyStickListener* argPQJoyStickListener)
	{
		this->listeners.remove(argPQJoyStickListener);
	}

	/**
	 * Updates the keyboard state
	 * @return		void
	 */
	void QJoyStick::UpdateState()
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
				this->pState->KEY_1 = (bool)((jState.rgbButtons[0] & 0x80) != 0);
				this->pState->KEY_2 = (bool)((jState.rgbButtons[1] & 0x80) != 0);
				this->pState->KEY_3 = (bool)((jState.rgbButtons[2] & 0x80) != 0);
				this->pState->KEY_4 = (bool)((jState.rgbButtons[3] & 0x80) != 0);
				this->pState->KEY_5 = (bool)((jState.rgbButtons[4] & 0x80) != 0);
				this->pState->KEY_6 = (bool)((jState.rgbButtons[5] & 0x80) != 0);
				this->pState->KEY_7 = (bool)((jState.rgbButtons[6] & 0x80) != 0);
				this->pState->KEY_8 = (bool)((jState.rgbButtons[7] & 0x80) != 0);
				if (key == "JOY_X")
				{
					this->pState->JOY_X = jState.lX;
				}

				//std::stringstream ss;
				//ss << "JOY INPUT" << std::endl;
				//ss << "JOY_X: " << this->pState->JOY_X << std::endl;
				//Logger::Log(ss.str(), 0, 0, 0);
			}
			// Tell our fans
			this->NotifyListeners();
		}
	}
}