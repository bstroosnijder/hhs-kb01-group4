#include "..\..\..\Header Files\engine\input\Keyboard.h"

namespace engine
{
	//no clue why we need this
	#define KEYDOWN(name, key) (name[key] & 0x80) 
	
	/**
	 * Compiler wants a empty constructor
	 * @author Alex Hodes
	 */
	Keyboard::Keyboard()
	{
		
	}


	/**
	 * Constructs the keyboard
	 * @author Alex Hodes
	 */
	Keyboard::Keyboard(HWND argHwnd,LPDIRECTINPUT8 argdInput,LPDIRECTINPUTDEVICE8 argdDevice)
	{
		dInput	= argdInput; 
		dDevice	= argdDevice; 
		hwnd	= argHwnd;
		InitKeyboard();
	}

	/**
	 * todo
	 * @author Alex Hodes
	 */
	Keyboard::~Keyboard()
	{
	}

	/**
	 * checks if device creating, Dataformat and cooperativelevel succeeds 
	 * @return	True of succeeds and false if something fails 
	 * @author	Alex Hodes
	 */
	bool Keyboard::InitKeyboard()
	{
		
		HRESULT hr = this->dInput->CreateDevice( GUID_SysKeyboard, &dDevice, NULL );
		if FAILED( hr ) 
		{ 
			SaveReleaseDevice(); 
			Logger::Log("Keyboard: Creating device failed",Logger::LOG_LEVEL_WARNING,__FILE__,__LINE__);
			return false; 
		}

		hr = this->dDevice->SetDataFormat( &c_dfDIKeyboard ); 
		if FAILED( hr ) 
		{ 
			SaveReleaseDevice(); 
			Logger::Log("Keyboard: Setting dataformat failed",Logger::LOG_LEVEL_WARNING,__FILE__,__LINE__);
			return false; 
		} 

		hr = this->dDevice->SetCooperativeLevel( hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND );
		if FAILED( hr )
		{ 
			SaveReleaseDevice(); 
			Logger::Log("Keyboard: Setting cooperativelevel failed",Logger::LOG_LEVEL_WARNING,__FILE__,__LINE__);
			return false; 
		} 
		Logger::Log("Keyboard created correctly",Logger::LOG_LEVEL_INFO,__FILE__,__LINE__);
		return true; 
	}
	/**
	 * Is a safe delete
	 * @param	void
	 * @author	Alex Hodes
	 */
	void Keyboard::SaveReleaseDevice()
	{ 
		if (dInput) 
		{ 
			if (dDevice) 
			{ 
				dDevice->Unacquire(); 
				dDevice->Release();
				dDevice = NULL; 
			} 
			dInput->Release();
			dInput = NULL; 
		}  
	
	}
	
		/**
		 * This method acquires the keyboard in case its lost.
		 * return	bool		true if device is acquired. Else its false
		 * @author	Alex Hodes
		 */
	bool Keyboard::DoAcquire()
	{
		int times = 5;
		for( int i = 0; i < times; i++ )
		{
			if( SUCCEEDED( dDevice->Acquire() ) )
			{
				return true;
			}
		}
		return false;
	}

		/**
		 * This method acquires the keyboard in case its lost.
		 * return	bool		true if KEYDOWN is eqaul to argKeyPressed. False if not
		 * @author	Alex Hodes
		 */
	bool Keyboard::ProcessKBInput(byte argKeyPressed) 
	{ 
		byte keyBuffer[256];
		if(!SUCCEEDED( dDevice->Poll() ))
		{
			DoAcquire();
		}
		
		dDevice->GetDeviceState( sizeof( keyBuffer ) , (LPVOID)&keyBuffer );
	
		// Check if keybuffer contains given key
		int pressed = KEYDOWN( keyBuffer, argKeyPressed );
		// pressed == 0 or 128 (0x80); meaning false or true
		if( pressed == 0 )
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}