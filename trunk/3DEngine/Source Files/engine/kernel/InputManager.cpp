#include "..\..\..\Header Files\engine\kernel\InputManager.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Constructs the InputManager object.
	 * And create the input device (see method comments for more info)
	 */
	InputManager::InputManager()
	{
		CreateInputDevice();
	}

	/**
	 * Destructs the InputManager object.
	 * @return		void
	 */
	InputManager::~InputManager()
	{
		this->CleanUp();
	}


	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void InputManager::CleanUp()
	{

	}

	/**
	 * This creates the directinput8 device. 
	 * This only happens once and all physical devices(mouse keyboard) use this direct input object 
	 * @return		bool		false if creating fails and true if succededs
	 * @author		Alex Hodes
	 */
	bool InputManager::CreateInputDevice()
	{
		dInput	= NULL; 
		HRESULT hr = DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput, NULL ); 
		if FAILED( hr ) 
		{
			return false;
		}
		return true;
	}

	/**
	 * This creates the keyboard object 
	 * This only happens for the main file. 
	 * Becuase keyboard needs a HWND to function correctly.
	 * @param		Window*		argPWindow   this window get casted to a win32window and gets the hwnd which is not known within the window class 
	 * @return		void
	 * @author		Alex Hodes
	 */

	void InputManager::CreateKeyboard(Window* argPWindow)
	{
		Win32Window* pWindow = (Win32Window*)argPWindow;
		HWND hwnd = pWindow -> GetHWin();
		keyboard = Keyboard(hwnd,this->dInput,this->dDevice);
	}

	/**
	 * This method checks if a curtain key is pressed.
	 * This method is used in the heartbeat loop in the kernel class.
	 * Therefor this method is called per frame.
	 * @return		void
	 * @author		Alex Hodes
	 */
	void InputManager::InputBeat()
	{
		if (DIK_W)
		{
			bool i = keyboard.ProcessKBInput(DIK_W);
			if(i == true)
			{
				Logger::Log("Naar voren",Logger::LOG_LEVEL_INFO,0,0);
			}
		}
		if (DIK_A)
		{
			bool i = keyboard.ProcessKBInput(DIK_A);
			if(i == true)
			{
				Logger::Log("Naar links",Logger::LOG_LEVEL_INFO,0,0);
			}
		}
		if (DIK_D)
		{
			bool i = keyboard.ProcessKBInput(DIK_D);
			if(i == true)
			{
				Logger::Log("Naar rechts",Logger::LOG_LEVEL_INFO,0,0);
			}
		}
		if (DIK_S)
		{
			bool i = keyboard.ProcessKBInput(DIK_S);
			if(i == true)
			{
				Logger::Log("Naar achteren",Logger::LOG_LEVEL_INFO,0,0);
			}
			
		}
	}
}
