#include "..\..\..\Header Files\engine\input\Keyboard.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---

	//no clue why we need this
	#define KEYDOWN(name, key) (name[key] & 0x80)

	//---Private methods---
	//---Public methods---

	/**
	 * Constructs the keyboard
	 * @param		HWND						The window that is receiving input
	 * @param		LPDIRECTINPUT8				???
	 */
	Keyboard::Keyboard(Window* argPWindow, LPDIRECTINPUT8 argPInput)
	{
		Logger::Log("Keyboard: Creating", Logger::INFO, __FILE__, __LINE__);

		this->keymap = std::list<std::string>();

		Win32Window* pWindow = (Win32Window*)argPWindow;

		argPInput->CreateDevice(GUID_SysKeyboard, &this->pDevice, NULL);
		this->pDevice->SetDataFormat(&c_dfDIKeyboard);
		this->pDevice->SetCooperativeLevel(pWindow->GetHWin(), DISCL_EXCLUSIVE | DISCL_FOREGROUND);

		// Init the keyboard state
		this->pState = new KeyboardState();

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
			delete this->pDevice;
		}
	}

	/**
	 * Adds a key to the keymap
	 * @param		std::string					The key to add to the keymap
	 * @return		void
	 */
	void Keyboard::RegisterKey(std::string argKey)
	{
		this->keymap.push_back(argKey);
	}
	
	/**
	 * This method acquires the keyboard in case its lost.
	 * @return		bool						true if device is acquired. Else its false
	 */
	bool Keyboard::DoAcquire()
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
	 * Gets for the keyboard state
	 * @return		KeyboardState*
	 */
	KeyboardState* Keyboard::GetState()
	{
		return this->pState;
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
			DoAcquire();
		}
		else
		{
			this->pDevice->GetDeviceState(sizeof(keyBuffer), (LPVOID)&keyBuffer);

			std::list<std::string>::iterator keymapIt;
			for(keymapIt = this->keymap.begin(); keymapIt != this->keymap.end(); keymapIt++)
			{
				std::string key = *keymapIt;
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
		}
	}
}