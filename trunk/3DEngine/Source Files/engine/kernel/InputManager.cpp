#include "..\..\..\Header Files\engine\kernel\InputManager.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---

	void InputManager::NotifyObservers()
	{
		for each(InputObserver* pInputObserver in this->pObservers)
		{
			pInputObserver->Notify(this->pKeyboardState);
		}
	}

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

		this->pKeyboard = NULL;
		this->pMouse = NULL;

		this->pKeyboardState = new KeyboardState();
		this->pMouseState = new MouseState();

		this->pObservers = std::list<InputObserver*>();

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
		this->pMouse			= new Mouse(argPWindow, this->pInput);
	}

	/**
	 * This method checks if a curtain key is pressed.
	 * This method is used in the heartbeat loop in the kernel class.
	 * Therefor this method is called per frame.
	 * @return		void
	 */
	void InputManager::InputBeat()
	{
		// If we have a keyboard, process it
		if(this->pKeyboard != NULL)
		{
			if(DIK_W)
			{
				this->pKeyboardState->KEY_W			= this->pKeyboard->ProcessKBInput(DIK_W);
			}
			if(DIK_S)
			{
				this->pKeyboardState->KEY_S			= this->pKeyboard->ProcessKBInput(DIK_S);
			}
			if(DIK_A)
			{
				this->pKeyboardState->KEY_A			= this->pKeyboard->ProcessKBInput(DIK_A);
			}
			if(DIK_D)
			{
				this->pKeyboardState->KEY_D			= this->pKeyboard->ProcessKBInput(DIK_D);
			}
			if(DIK_Q)
			{
				this->pKeyboardState->KEY_Q			= this->pKeyboard->ProcessKBInput(DIK_Q);
			}
			if(DIK_E)
			{
				this->pKeyboardState->KEY_E			= this->pKeyboard->ProcessKBInput(DIK_E);
			}
			if(DIK_LSHIFT)
			{
				this->pKeyboardState->KEY_LSHIFT	= this->pKeyboard->ProcessKBInput(DIK_LSHIFT);
			}
			if(DIK_SPACE)
			{
				this->pKeyboardState->KEY_SPACE		= this->pKeyboard->ProcessKBInput(DIK_SPACE);
			}
			if(DIK_HOME)
			{
				this->pKeyboardState->KEY_HOME		= this->pKeyboard->ProcessKBInput(DIK_HOME);
			}
		}
		
		// If we have a mouse, process it
		if(this->pMouse != NULL)
		{
		}

		// Tell our fans! :D

		if(!SUCCEEDED(this->pMouse->GetDevice()->Poll())) 
		{
			this->pMouse->DoAcquire();
		}

		DIDEVICEOBJECTDATA od;
		DWORD elements = 0;

		HRESULT hr = this->pMouse->GetDevice()->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), &od, &elements, 0 );

		/*if(FAILED(hr)) {
			Logger::Log("FAIL", Logger::FATAL, __FILE__, __LINE__);
		} else {
			Logger::Log("SUCCESS!", Logger::FATAL, __FILE__, __LINE__);
		}*/

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

		this->NotifyObservers();
	}

	void InputManager::AddObserver(InputObserver* argPInputObserver)
	{
		this->pObservers.push_back(argPInputObserver);
	}

	void InputManager::RemoveObserver(InputObserver* argPInputObserver)
	{
		this->pObservers.remove(argPInputObserver);
	}
}
