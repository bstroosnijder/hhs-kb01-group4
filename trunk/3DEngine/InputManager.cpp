#include "InputManager.h"

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
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void InputManager::CleanUp()
	{

	}
}
