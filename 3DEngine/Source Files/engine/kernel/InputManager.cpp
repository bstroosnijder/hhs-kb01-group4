#include "..\..\..\Header Files\engine\kernel\InputManager.h"

namespace engine
{
	//---Private attributes---

	bool InputManager::HasJoyStick					= false;

	//---Public attributes---

	const unsigned long InputManager::KEYBOARD		= 0;
	const unsigned long InputManager::MOUSE			= 1;
	const unsigned long InputManager::JOYSTICK		= 2;

	//---Private methods---
	//---Public methods---

	/**
	 * Constructs the InputManager object.
	 * And create the input device (see method comments for more info)
	 */
	InputManager::InputManager()
	{
		Logger::Log("InputManager: Initializing", Logger::INFO, __FILE__, __LINE__);

		this->pInput		= NULL;
		// Create the input object
		DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&this->pInput, NULL);

		this->pKeyboard		= NULL;
		this->pMouse		= NULL;
		this->pJoyStick		= NULL;

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
		delete this->pJoyStick;

		// Safly delete the input object
		if(this->pInput != NULL)
		{
			this->pInput->Release();
		}
	}

	/**
	 * @param		LPCDIDEVICEINSTANCE		The instance of the device
	 * @param		void*					???

	 */
	BOOL CALLBACK InputManager::SetupDeviceCallback(LPCDIDEVICEINSTANCE lpddi, void* pvRef)
	{
		InputManager::HasJoyStick = true;
		return DIENUM_STOP;
	}

	/**
	 * This creates the keyboard object 
	 * This only happens for the main file. 
	 * Becuase keyboard needs a HWND to function correctly.
	 * @param		Window*				this window get casted to a win32window and gets the hwnd which is not known within the window class 
	 * @return		void
	 */
	void InputManager::SetupDevices(Window* argPWindow)
	{
		// Create a new keyboard device
		this->pKeyboard			= new Keyboard(argPWindow, this->pInput);
		// Create a new mouse device
		this->pMouse			= new Mouse(argPWindow, this->pInput);
		// Create a new joystick device
		this->pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, InputManager::SetupDeviceCallback, NULL, DIEDFL_ATTACHEDONLY);
		if(InputManager::HasJoyStick)
		{
			this->pJoyStick		= new QJoyStick(argPWindow, this->pInput);
		}
	}

	/**
	 * Gets the keyboard object
	 * @return		Keyboard*
	 */
	Keyboard* InputManager::GetKeyboard()
	{
		return this->pKeyboard;
	}

	/**
	 * Gets the mouse object
	 * @return		Mouse*
	 */
	Mouse* InputManager::GetMouse()
	{
		return this->pMouse;
	}

	/**
	 * Gets the mouse object
	 * @return		Mouse*
	 */
	QJoyStick* InputManager::GetJoyStick()
	{
		return this->pJoyStick;
	}

	/**
	 * Checks whether a device is created
	 * @param		unsigned long		The device index to check
	 * @return		bool
	 */
	bool InputManager::HasDevice(unsigned long argDeviceIndex)
	{
		bool hasDevice = false;
		if(	(argDeviceIndex == InputManager::KEYBOARD && this->pKeyboard != NULL) ||
			(argDeviceIndex == InputManager::MOUSE && this->pMouse != NULL) ||
			(argDeviceIndex == InputManager::JOYSTICK && this->pJoyStick != NULL))
		{
			hasDevice = true;
		}

		return hasDevice;
	}
	
	/**
	 * Gets a device
	 * @param		unsigned long		The device index to check
	 * @return		InputDevice*
	 */
	InputDevice* InputManager::GetDevice(unsigned long argDeviceIndex)
	{
		InputDevice* pDevice;
		if(argDeviceIndex == InputManager::KEYBOARD)
		{
			pDevice = this->pKeyboard;
		}
		else if(argDeviceIndex == InputManager::MOUSE)
		{
			pDevice = this->pMouse;
		}
		else if(argDeviceIndex == InputManager::JOYSTICK)
		{
			pDevice = this->pJoyStick;
		}
		else
		{
			pDevice = NULL;
		}

		return pDevice;
	}

	/**
	 * Updates a device
	 * @param		unsigned long		The device index to check
	 * @return		void
	 */
	void InputManager::UpdateDevice(unsigned long argDeviceIndex)
	{
		if(argDeviceIndex == InputManager::KEYBOARD)
		{
			this->pKeyboard->UpdateState();
		}
		else if(argDeviceIndex == InputManager::MOUSE)
		{
			this->pMouse->UpdateState();
		}
		else if(argDeviceIndex == InputManager::JOYSTICK)
		{
			this->pJoyStick->UpdateState();
		}
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
			this->pKeyboard->UpdateState();
		}
		
		// If we have a mouse, process it
		if(this->pMouse != NULL)
		{
			this->pMouse->UpdateState();
		}

		// If we have a joystick, process it
		if(this->pJoyStick != NULL)
		{
			this->pJoyStick->UpdateState();
		}
	}
}
