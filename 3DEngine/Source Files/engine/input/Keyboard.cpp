#include "..\..\..\Header Files\engine\input\Keyboard.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---

	// Macro to check if a key is down
	#define KEYDOWN(name, key) (name[key] & 0x80)

	//---Private methods---
	//---Public methods---

	/**
	 * Constructs the keyboard
	 * @param		HWND						The window that is receiving input
	 * @param		LPDIRECTINPUT8				???
	 */
	Keyboard::Keyboard(Window* argPWindow, LPDIRECTINPUT8 argPInput) : InputDevice()
	{
		Logger::Log("Keyboard: Creating", Logger::INFO, __FILE__, __LINE__);
		Win32Window* pWindow = (Win32Window*)argPWindow;

		argPInput->CreateDevice(GUID_SysKeyboard, &this->pDevice, NULL);
		this->pDevice->SetDataFormat(&c_dfDIKeyboard);
		this->pDevice->SetCooperativeLevel(pWindow->GetHWin(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

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
	 * Updates the keyboard state
	 * @return		void
	 */
	void Keyboard::UpdateState()
	{
		if(!SUCCEEDED(this->pDevice->Poll()))
		{
			this->DoAcquire();
		}
		else
		{
			byte kState[256];
			this->pDevice->GetDeviceState(sizeof(kState), (LPVOID)&kState);

			std::map<std::string, std::string>::iterator bindsIt;
			for(bindsIt = this->binds.begin(); bindsIt != this->binds.end(); bindsIt++)
			{
				std::string key		= bindsIt->first;
				std::string bind	= bindsIt->second;
				float speed			= 1.0f;

				if(	(key == "KEY_A"			&& (bool)(KEYDOWN(kState, DIK_A) != 0)) ||
					(key == "KEY_D"			&& (bool)(KEYDOWN(kState, DIK_D) != 0)) ||
					(key == "KEY_E"			&& (bool)(KEYDOWN(kState, DIK_E) != 0)) ||
					(key == "KEY_Q"			&& (bool)(KEYDOWN(kState, DIK_Q) != 0)) ||
					(key == "KEY_S"			&& (bool)(KEYDOWN(kState, DIK_S) != 0)) ||
					(key == "KEY_W"			&& (bool)(KEYDOWN(kState, DIK_W) != 0)) ||
					(key == "KEY_DOWN"		&& (bool)(KEYDOWN(kState, DIK_DOWN) != 0)) ||
					(key == "KEY_HOME"		&& (bool)(KEYDOWN(kState, DIK_HOME) != 0)) ||
					(key == "KEY_LEFT"		&& (bool)(KEYDOWN(kState, DIK_LEFT) != 0)) ||
					(key == "KEY_LSHIFT"	&& (bool)(KEYDOWN(kState, DIK_LSHIFT) != 0)) ||
					(key == "KEY_RIGHT"		&& (bool)(KEYDOWN(kState, DIK_RIGHT) != 0)) ||
					(key == "KEY_SPACE"		&& (bool)(KEYDOWN(kState, DIK_SPACE) != 0)) ||
					(key == "KEY_UP"		&& (bool)(KEYDOWN(kState, DIK_UP) != 0)))
				{
					// Tell our fans
					this->NotifyInputListeners(bind, speed);
				}
			}
		}
	}
}