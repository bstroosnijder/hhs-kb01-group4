#ifndef CAMERA_H_
#define CAMERA_H_

#include <map>
#include <string>
#include "..\..\logger\Logger.h"
#include "..\Entity.h"
#include "..\..\input\listeners\KeyboardListener.h"
#include "..\..\input\KeyboardState.h"
#include "..\..\input\listeners\MouseListener.h"
#include "..\..\input\MouseState.h"
#include "..\..\input\listeners\JoyStickListener.h"
#include "..\..\input\JoyStickState.h"
#include "..\..\renderer\Renderer.h"

namespace engine
{
	/**
	 * Because we aren't allowed to use the view matrix to move our view we have to do an extra multiplication on our world matrix.
	 * The camera takes care of this. It Acts the same as a normal entity would except that it flips the world matrix.
	 * this is because if we want to move the view 10 forward, we have to move the world 10 backward.
	 */
	class Camera : public Entity, public KeyboardListener, public MouseListener, public JoyStickListener
	{
	private:
		void DoBind(std::string argBind, float argSpeed);
	public:
		Camera();
		~Camera();
		void CleanUp();
		
		void DoKeyboardEvent(std::map<std::string, std::string> argBinds, KeyboardState* argPState);
		void DoMouseEvent(std::map<std::string, std::string> argBinds, MouseState* argPState);
		void DoJoyStickEvent(std::map<std::string, std::string> argBinds, JoyStickState* argPState);

		void Update();
		void Draw(Renderer* argPRenderer);
	};
}

#endif