#include "..\..\..\Header Files\engine\input\Mouse.h"

namespace engine
{
	//---Private attributes---

	#define KEYDOWN(name, key) (name[key] & 0x80)

	//---Public attributes---
	//---Private methods---
	//---Public methods---
	
	/**
	 * Constructs the keyboard
	 */
	Mouse::Mouse(Window* argPWindow, LPDIRECTINPUT8 argPInput)
	{
		Logger::Log("Mouse: Creating", Logger::INFO, __FILE__, __LINE__);

		Win32Window* pWindow = (Win32Window*)argPWindow;

		// - size of enclosing structure
        dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
        // - always size of DIPROPHEADER
        dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
        // - identifier for property in question - 0 for entire device
        dipdw.diph.dwObj        = 0;
        // - DIPH_DEVICE since entire device is involved
        dipdw.diph.dwHow        = DIPH_DEVICE;
        // property data member (takes a single word of data)
        // - the buffer size goes here
        dipdw.dwData            = 200;

		argPInput->CreateDevice(GUID_SysMouse, &this->pDevice, NULL);
		this->pDevice->SetDataFormat(&c_dfDIMouse2);
		this->pDevice->SetCooperativeLevel(pWindow->GetHWin(), DISCL_EXCLUSIVE | DISCL_FOREGROUND);

		this->pDevice->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );

		this->keymap = std::list<std::string>();
		this->pState = new MouseState();

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

	
	MouseState* Mouse::GetState()
	{
		return this->pState;
	}

	
	/**
	 * This method acquires the mouse in case its lost.
	 * @return		bool						true if device is acquired. Else its false
	 */
	bool Mouse::DoAcquire()
	{
		int times = 5;
		for(int i = 0; i < times; i++)
		{
			if(SUCCEEDED(this->pDevice->Acquire()))
			{
				return true;
			}
		}

		return false;
	}

	/**
	 * Adds a key to the keymap
	 * @param		std::string					The key to add to the keymap
	 * @return		void
	 */
	void Mouse::RegisterKey(std::string argKey)
	{
		this->keymap.push_back(argKey);
	}

	/**
	 * Updates the mouse state
	 * @return		void
	 */
	void Mouse::UpdateState()
	{
		byte keyBuffer[256];
		if(!SUCCEEDED(this->pDevice->Poll())) 
		{			
			this->DoAcquire();
		}
		else
		{
			this->pDevice->GetDeviceState(sizeof(keyBuffer), (LPVOID)&keyBuffer);

			DIDEVICEOBJECTDATA od;
			DWORD elements = 1;

			HRESULT hr = this->pDevice->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), &od, &elements, 0 );

			if(hr == DIERR_INVALIDPARAM) 
			{
				Logger::Log("Mouse: Invalid paramater detected.", Logger::FATAL, __FILE__, __LINE__);
				return;
			}
			if(hr == DIERR_NOTBUFFERED) 
			{
				Logger::Log("Mouse: Mouse is not buffered.", Logger::FATAL, __FILE__, __LINE__);
				return;
			}
			if(hr == DIERR_NOTINITIALIZED) 
			{
				Logger::Log("Mouse: Mouse could not be initialized.", Logger::FATAL, __FILE__, __LINE__);
				return;
			}

			std::list<std::string>::iterator keymapIt;
			for(keymapIt = this->keymap.begin(); keymapIt != this->keymap.end(); keymapIt++)
			{
				std::string key = *keymapIt;

				if(key == "MOUSE_LEFT")
				{
					this->pState->MOUSE_LEFT = od.dwOfs == DIMOFS_X;
				}
				else if(key == "MOUSE_RIGHT")
				{
					this->pState->MOUSE_RIGHT = (bool)(KEYDOWN(keyBuffer, DIK_D) != 0);
				}
				else if(key == "MOUSE_UP")
				{
					this->pState->MOUSE_UP = (bool)(KEYDOWN(keyBuffer, DIK_E) != 0);
				}
				else if(key == "MOUSE_DOWN")
				{
					this->pState->MOUSE_DOWN = (bool)(KEYDOWN(keyBuffer, DIK_Q) != 0);
				}
				else if(key == "KEY_LMB")
				{
					this->pState->KEY_LMB = (bool)(KEYDOWN(keyBuffer, DIK_S) != 0);
				}
				else if(key == "KEY_RMB")
				{
					this->pState->KEY_RMB = (bool)(KEYDOWN(keyBuffer, DIK_W) != 0);
				}

				if(od.dwOfs == DIMOFS_X) 
				{
					// Mouse horizontal motion		
					Logger::Log("Horizontal mouse movement detected", Logger::INFO, __FILE__, __LINE__);
				}
				if(od.dwOfs == DIMOFS_Y) 
				{
					// Mouse vertical motion		
					Logger::Log("Vertical mouse movement detected", Logger::INFO, __FILE__, __LINE__);
				}
				if(od.dwOfs == DIMOFS_BUTTON0)
				{
					if(od.dwSequence % 2 == 0)
					{
						Logger::Log("Mousebutton detected", Logger::INFO, __FILE__, __LINE__);
					}
				}
				if(od.dwOfs == DIMOFS_BUTTON1)
				{
					if(od.dwSequence % 2 == 0)
					{
						Logger::Log("Right-Mousebutton detected", Logger::INFO, __FILE__, __LINE__);
					}
				}
			}
		}
	}
}