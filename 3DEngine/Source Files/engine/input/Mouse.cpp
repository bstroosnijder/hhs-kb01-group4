#include "..\..\..\Header Files\engine\input\Mouse.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---
	
	/**
	 * Constructs the keyboard
	 */
	Mouse::Mouse()
	{
	}

	/**
	 * Destructs the Keyboard object.
	 */
	Mouse::~Mouse()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing this object.
	 * @return		void
	 */
	void Mouse::CleanUp()
	{
		if (this->pDevice != NULL)
		{
			this->pDevice->Unacquire();
			this->pDevice->Release();
			delete this->pDevice;
		}
	}

	/**
	 * TODO
	 */
	bool Mouse::InitMouse()
	{
		return true;
	}
	
	/**
	 * TODO
	 */
	bool Mouse::DoAcquire()
	{
		return true;
	}
	
	/**
	 * TODO
	 */
	void Mouse::SetMouseBuffer()
	{
	}
}