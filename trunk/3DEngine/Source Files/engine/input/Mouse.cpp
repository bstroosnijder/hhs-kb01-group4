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

		argPInput->CreateDevice(GUID_SysMouse, &this->pDevice, NULL);
		this->pDevice->SetDataFormat(&c_dfDIMouse);
		this->pDevice->SetCooperativeLevel(pWindow->GetHWin(), DISCL_EXCLUSIVE | DISCL_FOREGROUND);

		LPCDIPROPHEADER size = NULL;

		this->pDevice->SetProperty( DIPROP_BUFFERSIZE, size );

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

	LPDIRECTINPUTDEVICE8 Mouse::GetDevice()
	{
		return this->pDevice;
	}

	/**
	 * TODO
	 */
	bool Mouse::InitMouse()
	{
		return true;
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
	 * TODO
	 */
	void Mouse::SetMouseBuffer()
	{
	}
}