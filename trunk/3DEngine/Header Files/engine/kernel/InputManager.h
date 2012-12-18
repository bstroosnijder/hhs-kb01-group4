#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <d3d9.h>
#include <dinput.h>//include kan foutief zijn. Wij hebben niet de juiste includes opgeschreven
#include <DXGI.h>  //''
#include "WindowManager.h"
#include "..\scene\entities\camera.h"

namespace engine
{
	/**
	 * This class is responsible for listening to, and handling of, user input.
	 * Any input from the user, such as keyboard and mouse clicks, will be registered, handled and dispatched by this class.
	 */
	class InputManager
	{
	public:
		InputManager();
		~InputManager();
		InputManager(WindowManager* argPWindowManager);
		void CleanUp();
		void RegistrateObserver(Camera* argPCamera);
	};
}

#endif