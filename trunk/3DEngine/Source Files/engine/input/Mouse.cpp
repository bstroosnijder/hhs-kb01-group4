#include "..\..\..\Header Files\engine\input\Mouse.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---
	
	/**
	 * Constructs the keyboard
	 */
	Mouse::Mouse(Window* argPWindow, LPDIRECTINPUT8 argPInput) : InputDevice()
	{
		Logger::Log("Mouse: Creating", Logger::INFO, __FILE__, __LINE__);
		Win32Window* pWindow = (Win32Window*)argPWindow;

		DIPROPDWORD mData;
		// - size of enclosing structure
		mData.diph.dwSize       = sizeof(DIPROPDWORD);
		// - always size of DIPROPHEADER
		mData.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		// - identifier for property in question - 0 for entire device
		mData.diph.dwObj        = 0;
		// - DIPH_DEVICE since entire device is involved
		mData.diph.dwHow        = DIPH_DEVICE;
		// property data member (takes a single word of data)
		// - the buffer size goes here
		mData.dwData            = 2;

		argPInput->CreateDevice(GUID_SysMouse, &this->pDevice, NULL);
		this->pDevice->SetDataFormat(&c_dfDIMouse);
		this->pDevice->SetCooperativeLevel(pWindow->GetHWin(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		this->pDevice->SetProperty(DIPROP_BUFFERSIZE, &mData.diph);

		Logger::Log("Mouse: Finishing", Logger::INFO, __FILE__, __LINE__);
	}

	/**
	 * Destructs the Keyboard object.
	 */
	Mouse::~Mouse()
	{
		Logger::Log("Mouse: Disposing", Logger::INFO, __FILE__, __LINE__);
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing this object.
	 * @return		void
	 */
	void Mouse::CleanUp()
	{
		if (this->pDevice != NULL)
		{
			this->pDevice->Unacquire();
			this->pDevice->Release();
		}
	}

	/**
	 * Updates the mouse state
	 * @return		void
	 */
	void Mouse::UpdateState()
	{
		if(!SUCCEEDED(this->pDevice->Poll())) 
		{			
			this->DoAcquire();
		}
		else
		{
			DIMOUSESTATE mState;
			this->pDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mState);
			
			std::map<std::string, std::string>::iterator bindsIt;
			for(bindsIt = this->binds.begin(); bindsIt != this->binds.end(); bindsIt++)
			{
				std::string key		= bindsIt->first;
				std::string bind	= bindsIt->second;
				float speed			= 1.0f;

				if(	(key == "KEY_LMB" && (bool)((mState.rgbButtons[0] & 0x80) != 0)) ||
					(key == "KEY_LMB" && (bool)((mState.rgbButtons[1] & 0x80) != 0)))
				{
					// Tell our fans
					this->NotifyInputListeners(bind, speed);
				}
				else if(key == "MOUSE_X" && (bool)(mState.lX != 0))
				{
					speed = (mState.lX * 0.5f);
					// Tell our fans
					this->NotifyInputListeners(bind, speed);
				}
				else if(key == "MOUSE_Y" && (bool)(mState.lY != 0))
				{
					speed = (mState.lX * 0.5f);
					// Tell our fans
					this->NotifyInputListeners(bind, speed);
				}
			}
		}
	}
}