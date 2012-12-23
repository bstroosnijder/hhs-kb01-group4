#include "..\..\..\Header Files\engine\input\Keyboard.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---

	//no clue why we need this
	#define KEYDOWN(name, key) (name[key] & 0x80)

	//---Private methods---
	//---Public methods---

	/**
	 * Constructs the keyboard
	 * @param		HWND						The window that is receiving input
	 * @param		LPDIRECTINPUT8				???
	 */
	Keyboard::Keyboard(Window* argPWindow, LPDIRECTINPUT8 argPInput)
	{
		Logger::Log("Keyboard: Creating", Logger::INFO, __FILE__, __LINE__);

		Win32Window* pWindow = (Win32Window*)argPWindow;

		argPInput->CreateDevice(GUID_SysKeyboard, &this->pDevice, NULL);
		this->pDevice->SetDataFormat(&c_dfDIKeyboard);
		this->pDevice->SetCooperativeLevel(pWindow->GetHWin(), DISCL_EXCLUSIVE | DISCL_FOREGROUND);

		Logger::Log("Keyboard: Finished", Logger::INFO, __FILE__, __LINE__);
	}

	/**
	 * Destructs the Keyboard object.
	 */
	Keyboard::~Keyboard()
	{
		Logger::Log("Keyboard: Disposing", Logger::INFO, __FILE__, __LINE__);
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing this object.
	 * @return		void
	 */
	void Keyboard::CleanUp()
	{
		if (this->pDevice != NULL)
		{
			this->pDevice->Unacquire();
			this->pDevice->Release();
			delete this->pDevice;
		}
	}
	
	/**
	 * This method acquires the keyboard in case its lost.
	 * @return		bool						true if device is acquired. Else its false
	 */
	bool Keyboard::DoAcquire()
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
	 * This method acquires the keyboard in case its lost.
	 * @return		bool						true if KEYDOWN is eqaul to argKeyPressed. False if not
	 */
	bool Keyboard::ProcessKBInput(byte argKeyPressed) 
	{ 
		byte keyBuffer[256];
		if(!SUCCEEDED(this->pDevice->Poll()))
		{
			this->DoAcquire();
		}
		
		this->pDevice->GetDeviceState(sizeof(keyBuffer), (LPVOID)&keyBuffer);
	
		// Check if keybuffer contains given key
		int pressed = KEYDOWN(keyBuffer, argKeyPressed);
		// pressed == 0 or 128 (0x80); meaning false or true
		if(pressed == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}