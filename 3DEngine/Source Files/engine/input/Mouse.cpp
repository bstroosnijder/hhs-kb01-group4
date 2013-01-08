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
		this->pDevice->SetCooperativeLevel(pWindow->GetHWin(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		this->pDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

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
			unsigned long elements = 1;
			DIDEVICEOBJECTDATA data;
			HRESULT hr = this->pDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &data, &elements, 0);

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

			std::list<std::string>::iterator mouseKeymapIt;
			for(mouseKeymapIt = this->keymap.begin(); mouseKeymapIt != this->keymap.end(); mouseKeymapIt++)
			{
				std::string key = *mouseKeymapIt;

				if(key == "KEY_LMB")
				{
					if(data.dwOfs == DIMOFS_BUTTON0)
					{
						if(this->pState->KEY_LMB == true)
						{
							this->pState->KEY_LMB = false;
						}
						else
						{
							this->pState->KEY_LMB = true;
						}
					}
				}
				else if(key == "KEY_RMB")
				{
					if(data.dwOfs == DIMOFS_BUTTON1)
					{
						if(this->pState->KEY_RMB == true)
						{
							this->pState->KEY_RMB = false;
						}
						else
						{
							this->pState->KEY_RMB = true;
						}
					}
				}
				else if(key == "MOUSE_UP")
				{
					long speed = (long)data.dwData;
					this->pState->MOUSE_UP = 0;
					if(data.dwOfs == DIMOFS_Y && speed < 0)
					{
						this->pState->MOUSE_UP = -speed;
					}
				}
				else if(key == "MOUSE_DOWN")
				{
					long speed = (long)data.dwData;
					this->pState->MOUSE_DOWN = 0;
					if(data.dwOfs == DIMOFS_Y && speed > 0)
					{
						this->pState->MOUSE_DOWN = speed;
					}
				}
				else if(key == "MOUSE_LEFT")
				{
					long speed = (long)data.dwData;
					this->pState->MOUSE_LEFT = 0;
					if(data.dwOfs == DIMOFS_X && speed < 0)
					{
						this->pState->MOUSE_LEFT = -speed;
					}
				}
				else if(key == "MOUSE_RIGHT")
				{
					long speed = (long)data.dwData;
					this->pState->MOUSE_RIGHT = 0;
					if(data.dwOfs == DIMOFS_X && speed > 0)
					{
						this->pState->MOUSE_RIGHT = speed;
					}
				}
			}
		}
	}
}