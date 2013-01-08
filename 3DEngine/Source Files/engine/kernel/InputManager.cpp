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
			pInputObserver->Notify(this->keybinds, this->pKeyboard->GetState(), this->mousekeybinds, this->pMouse->GetState());
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
		this->keybinds		= std::map<std::string, std::string>();

		this->pInput		= NULL;
		// Create the input object
		DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&this->pInput, NULL);

		this->pKeyboard		= NULL;
		this->pMouse		= NULL;

		this->pMouseState	= new MouseState();

		this->pObservers	= std::list<InputObserver*>();

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
			this->pKeyboard->UpdateState();
		}
		
		// If we have a mouse, process it
		if(this->pMouse != NULL)
		{
			this->pMouse->UpdateState();
		}

		// Tell our fans! :D
		this->NotifyObservers();
	}
	
	/**
	 * Adds a new key to look out for
	 * @param		std::string			The key to listen to
	 * @param		std::string			The command to execute with this key
	 */
	void InputManager::RegisterKey(std::string argKey, std::string argBind)
	{
		this->pKeyboard->RegisterKey(argKey);
		this->keybinds[argKey] = argBind;
	}

	void InputManager::RegisterMouseKey(std::string argKey, std::string argBind)
	{
		this->pMouse->RegisterKey(argKey);
		this->mousekeybinds[argKey] = argBind;
	}

	/**
	 * Adds an observer to the input manager
	 * @param		InputObserver*		The observer that wil listen
	 * @return		void
	 */
	void InputManager::AddObserver(InputObserver* argPInputObserver)
	{
		this->pObservers.push_back(argPInputObserver);
	}
	
	/**
	 * Removes an observer from the input manager
	 * @param		InputObserver*		The observer that wil be removed
	 * @return		void
	 */
	void InputManager::RemoveObserver(InputObserver* argPInputObserver)
	{
		this->pObservers.remove(argPInputObserver);
	}
}
