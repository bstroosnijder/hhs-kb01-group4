#include "..\..\..\Header Files\engine\input\InputDevice.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---

	void InputDevice::NotifyInputListeners(std::string argBind, float argSpeed)
	{
		std::list<InputListener*>::iterator inputListenerIt;
		for(inputListenerIt = this->inputListeners.begin(); inputListenerIt != this->inputListeners.end(); inputListenerIt++)
		{
			InputListener* pInputListener = *inputListenerIt;
			pInputListener->InputEvent(argBind, argSpeed);
		}
	}

	//---Public methods---

	/**
	 * Constructs an input device
	 */
	InputDevice::InputDevice()
	{
		this->binds				= std::map<std::string, std::string>();
		this->inputListeners	= std::list<InputListener*>();
	}
	
	/**
	 * This method acquires the device in case its lost.
	 * @return		bool			True if device is acquired. Else its false
	 */
	bool InputDevice::DoAcquire()
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
	 * Adds a binding to track
	 * @param		std::string		The key to watch
	 * @param		std::string		The bind to link with the key
	 * @return		void
	 */
	void InputDevice::AddBind(std::string argKey, std::string argBind)
	{
		this->binds[argKey] = argBind;
	}

	void InputDevice::AddInputListener(InputListener* argPInputListener)
	{
		this->inputListeners.push_back(argPInputListener);
	}

	void InputDevice::RemoveInputListener(InputListener* argPInputListener)
	{
		this->inputListeners.remove(argPInputListener);
	}
}