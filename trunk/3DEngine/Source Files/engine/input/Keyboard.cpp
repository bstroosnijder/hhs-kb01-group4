#include "..\..\..\Header Files\engine\input\Keyboard.h"

namespace engine
{
	//no clue why we need this
	#define KEYDOWN(name, key) (name[key] & 0x80) 

	/**
	 * todo
	 * @author Alex Hodes
	 */
	Keyboard::Keyboard()
	{
		dInput	= NULL; 
		dDevice	= NULL; 
		hwnd	= NULL;
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
	 * todo
	 * @author Alex Hodes
	 */
	Keyboard::Keyboard(HWND argHwnd)
	{
		dInput	= NULL; 
		dDevice	= NULL; 
		hwnd	= argHwnd;
		InitKeyboard();
	}

	/**
	 * todo
	 * @author Alex Hodes
	 */
	bool Keyboard::InitKeyboard()
	{
		
		HRESULT hr = this->dInput->CreateDevice( GUID_SysKeyboard, &dDevice, NULL );
		if FAILED( hr ) 
		{ 
			SaveReleaseDevice(); 
			return false; 
		}

		hr = this->dDevice->SetDataFormat( &c_dfDIKeyboard ); 
		if FAILED( hr ) 
		{ 
			SaveReleaseDevice(); 
			return false; 
		} 

		hr = this->dDevice->SetCooperativeLevel( hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND );
		if FAILED( hr )
		{ 
			SaveReleaseDevice(); 
			return false; 
		} 

		return true; 
	}
	/**
	 * todo
	 * @author Alex Hodes
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
		 * todo
		 * @author Alex Hodes
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
		 * todo
		 * @author Alex Hodes
		 */
	void Keyboard::SetHWND(HWND argHWND)
	{
		argHWND = hwnd;
	}

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
		//Logger::Log("d",Logger::LOG_LEVEL_INFO,__FILE__,__LINE__);
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