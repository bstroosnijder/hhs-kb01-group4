#include "..\..\..\Header Files\engine\kernel\InputManager.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Constructs the InputManager object.
	 */
	InputManager::InputManager()
	{
		
	}

	/**
	 * Destructs the InputManager object.
	 * @return		void
	 */
	InputManager::~InputManager()
	{
		this->CleanUp();
	}

	/**
	 * Overloading Constructor to have a pointer to the windowmanager in order to get a HWND. 
	 * To pass on to keyboard and mouse
	 * @param	WindowManager*  argPWindowManager
	 */
	InputManager::InputManager(WindowManager*  argPWindowManager)
	{
		//argPWindowManager -> 
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void InputManager::CleanUp()
	{

	}
}
