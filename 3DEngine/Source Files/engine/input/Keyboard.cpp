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
				int doNotify					= 0;
				std::vector<std::string> keys	= explode(':', bindsIt->first);
				std::string bind				= bindsIt->second;
				float speed						= 1.0f;

				std::vector<std::string>::iterator keysIt;
				for(keysIt = keys.begin(); keysIt != keys.end(); keysIt++)
				{
					std::string key = *keysIt;
					if(	(key == "KEY_A"			&& (bool)(KEYDOWN(kState, DIK_A) != 0)) ||
						(key == "KEY_C"			&& (bool)(KEYDOWN(kState, DIK_C) != 0)) ||
						(key == "KEY_D"			&& (bool)(KEYDOWN(kState, DIK_D) != 0)) ||
						(key == "KEY_E"			&& (bool)(KEYDOWN(kState, DIK_E) != 0)) ||
						(key == "KEY_L"			&& (bool)(KEYDOWN(kState, DIK_L) != 0)) ||
						(key == "KEY_P"			&& (bool)(KEYDOWN(kState, DIK_P) != 0)) ||
						(key == "KEY_Q"			&& (bool)(KEYDOWN(kState, DIK_Q) != 0)) ||
						(key == "KEY_S"			&& (bool)(KEYDOWN(kState, DIK_S) != 0)) ||
						(key == "KEY_W"			&& (bool)(KEYDOWN(kState, DIK_W) != 0)) ||
						(key == "KEY_LCONTROL"	&& (bool)(KEYDOWN(kState, DIK_LCONTROL) != 0)) ||
						(key == "KEY_DOWN"		&& (bool)(KEYDOWN(kState, DIK_DOWN) != 0)) ||
						(key == "KEY_GRAVE"		&& (bool)(KEYDOWN(kState, DIK_GRAVE) != 0)) ||
						(key == "KEY_HOME"		&& (bool)(KEYDOWN(kState, DIK_HOME) != 0)) ||
						(key == "KEY_LEFT"		&& (bool)(KEYDOWN(kState, DIK_LEFT) != 0)) ||
						(key == "KEY_LSHIFT"	&& (bool)(KEYDOWN(kState, DIK_LSHIFT) != 0)) ||
						(key == "KEY_RIGHT"		&& (bool)(KEYDOWN(kState, DIK_RIGHT) != 0)) ||
						(key == "KEY_SPACE"		&& (bool)(KEYDOWN(kState, DIK_SPACE) != 0)) ||
						(key == "KEY_1"			&& (bool)(KEYDOWN(kState, DIK_1) != 0)) ||
						(key == "KEY_2"			&& (bool)(KEYDOWN(kState, DIK_2) != 0)) ||
						(key == "KEY_3"			&& (bool)(KEYDOWN(kState, DIK_3) != 0)) ||
						(key == "KEY_4"			&& (bool)(KEYDOWN(kState, DIK_4) != 0)) ||
						(key == "KEY_5"			&& (bool)(KEYDOWN(kState, DIK_5) != 0)) ||
						(key == "KEY_6"			&& (bool)(KEYDOWN(kState, DIK_6) != 0)) ||
						(key == "KEY_7"			&& (bool)(KEYDOWN(kState, DIK_7) != 0)) ||
						(key == "KEY_8"			&& (bool)(KEYDOWN(kState, DIK_8) != 0)) ||
						(key == "KEY_9"			&& (bool)(KEYDOWN(kState, DIK_9) != 0)) ||
						(key == "KEY_0"			&& (bool)(KEYDOWN(kState, DIK_0) != 0)) ||
						(key == "KEY_UP"		&& (bool)(KEYDOWN(kState, DIK_UP) != 0)))
					{
						doNotify++;
					}
				}
				
				if(doNotify == keys.size())
				{
					// Tell our fans
					this->NotifyInputListeners(bind, speed);
				}
			}
		}
	}
}