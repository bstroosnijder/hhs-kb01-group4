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
		this->pDevice->SetCooperativeLevel(pWindow->GetHWin(), DISCL_EXCLUSIVE | DISCL_FOREGROUND);

		this->pDevice->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );

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

	/**
	 * Updates the mouse state
	 * @return		void
	 */
	void Mouse::UpdateState()
	{
		if(!SUCCEEDED(this->pDevice->Poll())) 
		{			
			bool res = this->DoAcquire();
			if(res == true) {
				Logger::Log("Acquired!", Logger::INFO, __FILE__, __LINE__);
			} else {
				
				Logger::Log("Not acquired!", Logger::INFO, __FILE__, __LINE__);
			}
		}

		DIDEVICEOBJECTDATA od;
		DWORD elements = 1;

		HRESULT hr = this->pDevice->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), &od, &elements, 0 );

		if(hr == DIERR_INPUTLOST) {
			Logger::Log("INPUTLOST", Logger::FATAL, __FILE__, __LINE__);
		}
		if(hr == DIERR_INVALIDPARAM) {
			Logger::Log("PARAM", Logger::FATAL, __FILE__, __LINE__);
		}
		if(hr == DIERR_NOTACQUIRED) {
			Logger::Log("NOTACQ", Logger::FATAL, __FILE__, __LINE__);
		}
		if(hr == DIERR_NOTBUFFERED) {
			Logger::Log("NOTBUFF", Logger::FATAL, __FILE__, __LINE__);
		}
		if(hr == DIERR_NOTINITIALIZED) {
			Logger::Log("NOTINIT", Logger::FATAL, __FILE__, __LINE__);
		}

		std::stringstream ss;//create a stringstream
		ss << elements;//add number to the stream
		Logger::Log(ss.str(), Logger::INFO, __FILE__, __LINE__);

		switch (od.dwOfs) 
		{

			// Mouse horizontal motion
			case DIMOFS_X:
				Logger::Log("Horizontal mouse movement detected", Logger::INFO, __FILE__, __LINE__);
				break;

			// Mouse vertical motion
			case DIMOFS_Y:
				Logger::Log("Vertical mouse movement detected", Logger::INFO, __FILE__, __LINE__);
				break;

			case DIMOFS_BUTTON0:
				Logger::Log("Mousebutton detected", Logger::INFO, __FILE__, __LINE__);
				break;

			case DIMOFS_BUTTON1:
				Logger::Log("Mousebutton detected", Logger::INFO, __FILE__, __LINE__);
				break;
		}
	}
}