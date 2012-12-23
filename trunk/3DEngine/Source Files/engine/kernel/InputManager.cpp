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
		Logger::Log("InputManager: Initializing", Logger::INFO, __FILE__, __LINE__);

		this->pInput = NULL;
		// Create the input object
		DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&this->pInput, NULL);

		Logger::Log("InputManager: Finished", Logger::INFO, __FILE__, __LINE__);
	}

	/**
	 * Destructs the InputManager object.
	 */
	InputManager::~InputManager()
	{
		Logger::Log("InputManager: Disposing", Logger::INFO, __FILE__, __LINE__);
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void InputManager::CleanUp()
	{
		// We delete the keyboard and mouse first since they contain a device
		delete this->pKeyboard;
		delete this->pMouse;

		// Safly delete the input object
		if(this->pInput != NULL)
		{
			this->pInput->Release();
			delete this->pInput;
		}
	}

	/**
	 * This creates the keyboard object 
	 * This only happens for the main file. 
	 * Becuase keyboard needs a HWND to function correctly.
	 * @param		Window*		this window get casted to a win32window and gets the hwnd which is not known within the window class 
	 * @return		void
	 */
	void InputManager::SetupDevices(Window* argPWindow)
	{
		// Create a new keyboard device
		this->pKeyboard			= new Keyboard(argPWindow, this->pInput);
		// Create a new mouse device
		//this->pMouse			= new Mouse(argPWindow, this->pInput);
	}

	/**
	 * This method checks if a curtain key is pressed.
	 * This method is used in the heartbeat loop in the kernel class.
	 * Therefor this method is called per frame.
	 * @return		void
	 */
	void InputManager::InputBeat()
	{
		if (DIK_W)
		{
			bool i = this->pKeyboard->ProcessKBInput(DIK_W);
			if(i == true)
			{
				Logger::Log("Naar voren",Logger::INFO,0,0);
			}
		}
		if (DIK_A)
		{
			bool i = this->pKeyboard->ProcessKBInput(DIK_A);
			if(i == true)
			{
				Logger::Log("Naar links",Logger::INFO,0,0);
			}
		}
		if (DIK_D)
		{
			bool i = this->pKeyboard->ProcessKBInput(DIK_D);
			if(i == true)
			{
				Logger::Log("Naar rechts",Logger::INFO,0,0);
			}
		}
		if (DIK_S)
		{
			bool i = this->pKeyboard->ProcessKBInput(DIK_S);
			if(i == true)
			{
				Logger::Log("Naar achteren",Logger::INFO,0,0);
			}
			
		}
	}
}
