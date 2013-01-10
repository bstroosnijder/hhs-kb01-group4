#include "..\..\..\Header Files\engine\input\Keyboard.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---

	//no clue why we need this
	#define KEYDOWN(name, key) (name[key] & 0x80)

	//---Private methods---

	/**
	 * Notifies all the listener
	 * @return		void
	 */
	void Keyboard::NotifyListeners()
	{
		std::list<KeyboardListener*>::iterator listenerIt;
		for(listenerIt = this->listeners.begin(); listenerIt != this->listeners.end(); listenerIt++)
		{
			KeyboardListener* pKeyboardListener = *listenerIt;
			pKeyboardListener->DoKeyboardEvent(this->binds, this->pState);
		}
	}

	/**
	 * Reset the state of the keyboard
	 * @return		void
	 */
	void Keyboard::ResetState()
	{
		this->pState->KEY_A			= false;
		this->pState->KEY_D			= false;
		this->pState->KEY_E			= false;
		this->pState->KEY_Q			= false;
		this->pState->KEY_S			= false;
		this->pState->KEY_W			= false;
		this->pState->KEY_DOWN		= false;
		this->pState->KEY_HOME		= false;
		this->pState->KEY_LEFT		= false;
		this->pState->KEY_LSHIFT	= false;
		this->pState->KEY_RIGHT		= false;
		this->pState->KEY_SPACE		= false;
		this->pState->KEY_UP		= false;
	}

	//---Public methods---

	/**
	 * Constructs the keyboard
	 * @param		HWND						The window that is receiving input
	 * @param		LPDIRECTINPUT8				???
	 */
	Keyboard::Keyboard(Window* argPWindow, LPDIRECTINPUT8 argPInput) : InputDevice()
	{
		Logger::Log("Keyboard: Creating", Logger::INFO, __FILE__, __LINE__);
		this->listeners = std::list<KeyboardListener*>();
		Win32Window* pWindow = (Win32Window*)argPWindow;

		argPInput->CreateDevice(GUID_SysKeyboard, &this->pDevice, NULL);
		this->pDevice->SetDataFormat(&c_dfDIKeyboard);
		this->pDevice->SetCooperativeLevel(pWindow->GetHWin(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

		// Init the keyboard state
		this->pState = new KeyboardState();
		this->ResetState();

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
		}
	}

	/**
	 * Adds a listener to the device
	 * @param		InputListener*		The listener to add to the list
	 * @return		void
	 */
	void Keyboard::AddListener(KeyboardListener* argPKeyboardListener)
	{
		this->listeners.push_back(argPKeyboardListener);
	}

	/**
	 * Removes a listener from the device
	 * @param		InputListener*		The listener to remove from the list
	 * @return		void
	 */
	void Keyboard::RemoveListener(KeyboardListener* argPKeyboardListener)
	{
		this->listeners.remove(argPKeyboardListener);
	}

	/**
	 * Updates the keyboard state
	 * @return		void
	 */
	void Keyboard::UpdateState()
	{
		byte keyBuffer[256];
		if(!SUCCEEDED(this->pDevice->Poll()))
		{
			this->DoAcquire();
		}
		else
		{
			this->pDevice->GetDeviceState(sizeof(keyBuffer), (LPVOID)&keyBuffer);

			std::map<std::string, std::string>::iterator bindsIt;
			for(bindsIt = this->binds.begin(); bindsIt != this->binds.end(); bindsIt++)
			{
				std::string key		= bindsIt->first;
				std::string bind	= bindsIt->second;

				if(key == "KEY_A")
				{
					this->pState->KEY_A = (bool)(KEYDOWN(keyBuffer, DIK_A) != 0);
				}
				else if(key == "KEY_D")
				{
					this->pState->KEY_D = (bool)(KEYDOWN(keyBuffer, DIK_D) != 0);
				}
				else if(key == "KEY_E")
				{
					this->pState->KEY_E = (bool)(KEYDOWN(keyBuffer, DIK_E) != 0);
				}
				else if(key == "KEY_Q")
				{
					this->pState->KEY_Q = (bool)(KEYDOWN(keyBuffer, DIK_Q) != 0);
				}
				else if(key == "KEY_S")
				{
					this->pState->KEY_S = (bool)(KEYDOWN(keyBuffer, DIK_S) != 0);
				}
				else if(key == "KEY_W")
				{
					this->pState->KEY_W = (bool)(KEYDOWN(keyBuffer, DIK_W) != 0);
				}
				else if(key == "KEY_DOWN")
				{
					this->pState->KEY_DOWN = (bool)(KEYDOWN(keyBuffer, DIK_DOWN) != 0);
				}
				else if(key == "KEY_HOME")
				{
					this->pState->KEY_HOME = (bool)(KEYDOWN(keyBuffer, DIK_HOME) != 0);
				}
				else if(key == "KEY_LEFT")
				{
					this->pState->KEY_LEFT = (bool)(KEYDOWN(keyBuffer, DIK_LEFT) != 0);
				}
				else if(key == "KEY_LSHIFT")
				{
					this->pState->KEY_LSHIFT = (bool)(KEYDOWN(keyBuffer, DIK_LSHIFT) != 0);
				}
				else if(key == "KEY_RIGHT")
				{
					this->pState->KEY_RIGHT = (bool)(KEYDOWN(keyBuffer, DIK_RIGHT) != 0);
				}
				else if(key == "KEY_SPACE")
				{
					this->pState->KEY_SPACE = (bool)(KEYDOWN(keyBuffer, DIK_SPACE) != 0);
				}
				else if(key == "KEY_UP")
				{
					this->pState->KEY_UP = (bool)(KEYDOWN(keyBuffer, DIK_UP) != 0);
				}
			}

			// Tell our fans
			this->NotifyListeners();
		}
	}
}