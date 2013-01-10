#include "..\..\..\Header Files\engine\input\QJoyStick.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---

	//no clue why we need this
	#define KEYDOWN(name, key) (name[key] & 0x80)

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
			
			this->pState->KEY_1 = (bool)((jState.rgbButtons[0] & 0x80) != 0);
			

			// Tell our fans
			this->NotifyListeners();
		}
	}
}