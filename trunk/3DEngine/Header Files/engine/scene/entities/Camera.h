#ifndef CAMERA_H_
#define CAMERA_H_

#include "..\..\logger\Logger.h"
#include "..\Entity.h"
#include "..\..\input\InputObserver.h"
#include "..\..\input\KeyboardState.h"
#include "..\..\renderer\Renderer.h"

namespace engine
{
	/**
	 * Because we aren't allowed to use the view matrix to move our view we have to do an extra multiplication on our world matrix.
	 * The camera takes care of this. It Acts the same as a normal entity would except that it flips the world matrix.
	 * this is because if we want to move the view 10 forward, we have to move the world 10 backward.
	 */
	class Camera : public Entity, public InputObserver
	{
	public:
		Camera();
		~Camera();
		void CleanUp();

		void Update();
		void Draw(Renderer* argPRenderer);

		void Notify(std::map<std::string, std::string> argKeybinds, KeyboardState* argPKeyboardState);
	};
}

#endif