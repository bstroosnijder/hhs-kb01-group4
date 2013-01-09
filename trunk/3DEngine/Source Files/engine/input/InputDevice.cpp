#include "..\..\..\Header Files\engine\input\InputDevice.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Constructs an input device
	 */
	InputDevice::InputDevice()
	{
		this->binds		= std::map<std::string, std::string>();
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
}