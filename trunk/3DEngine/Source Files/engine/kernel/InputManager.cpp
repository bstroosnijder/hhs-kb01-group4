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
		CreateSomething();
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
		//Window window* = argPWindowManager -> GetWindow(0);
		CreateSomething();
		Keyboard kb = Keyboard();
		
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void InputManager::CleanUp()
	{

	}

	bool InputManager::CreateSomething()
	{
		dInput	= NULL; 
		HRESULT hr = DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput, NULL ); 
		if FAILED( hr ) 
		{
			return false;
		}
		return true;
	}
}
