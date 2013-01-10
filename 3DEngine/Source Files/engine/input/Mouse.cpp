#include "..\..\..\Header Files\engine\input\Mouse.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---

	#define KEYDOWN(name, key) (name[key] & 0x80)

	//---Private methods---

	/**
	 * Notifies all the listener
	 * @return		void
	 */
	void Mouse::NotifyListeners()
	{
		std::list<MouseListener*>::iterator listenerIt;
		for(listenerIt = this->listeners.begin(); listenerIt != this->listeners.end(); listenerIt++)
		{
			MouseListener* pMouseListener = *listenerIt;
			pMouseListener->DoMouseEvent(this->binds, this->pState);
		}
	}

	/**
	 * Reset the state of the keyboard
	 * @return		void
	 */
	void Mouse::ResetState()
	{
		this->pState->KEY_LMB		= false;
		this->pState->KEY_RMB		= false;
		this->pState->MOUSE_UP		= 0;
		this->pState->MOUSE_DOWN	= 0;
		this->pState->MOUSE_LEFT	= 0;
		this->pState->MOUSE_RIGHT	= 0;

		// testje
		this->pState->MOUSE_X		= 0;
		this->pState->MOUSE_Y		= 0;
	}

	//---Public methods---
	
	/**
	 * Constructs the keyboard
	 */
	Mouse::Mouse(Window* argPWindow, LPDIRECTINPUT8 argPInput) : InputDevice()
	{
		Logger::Log("Mouse: Creating", Logger::INFO, __FILE__, __LINE__);
		this->listeners = std::list<MouseListener*>();
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

		this->pState = new MouseState();
		this->ResetState();

		Logger::Log("Mouse: Finishing", Logger::INFO, __FILE__, __LINE__);
	}

	/**
	 * Destructs the Keyboard object.
	 */
	Mouse::~Mouse()
	{
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
			delete this->pDevice;
		}
	}

	/**
	 * Adds a listener to the device
	 * @param		InputListener*		The listener to add to the list
	 * @return		void
	 */
	void Mouse::AddListener(MouseListener* argPMouseListener)
	{
		this->listeners.push_back(argPMouseListener);
	}

	/**
	 * Removes a listener from the device
	 * @param		InputListener*		The listener to remove from the list
	 * @return		void
	 */
	void Mouse::RemoveListener(MouseListener* argPMouseListener)
	{
		this->listeners.remove(argPMouseListener);
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

				if(key == "MOUSE_X")
				{
					this->pState->MOUSE_X += mState.lX;
				}
				else if(key == "MOUSE_Y")
				{
					this->pState->MOUSE_Y += mState.lY;
				}
				else if(key == "KEY_LMB")
				{
					this->pState->KEY_LMB = (bool)((mState.rgbButtons[0] & 0x80) != 0);
				}
				else if(key == "KEY_RMB")
				{
					this->pState->KEY_RMB = (bool)((mState.rgbButtons[1] & 0x80) != 0);
				}
			}

			// Tell our fans
			this->NotifyListeners();
		}
	}
}