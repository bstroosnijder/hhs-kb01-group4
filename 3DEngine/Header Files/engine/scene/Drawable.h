#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "..\logger\Logger.h"
#include "..\renderer\Renderer.h"

namespace engine
{
	/**
	 * Represents anything that can be shown on the screen
	 */
	class Drawable
	{
		virtual void Update()=0;
		virtual void Draw(Renderer* argPRenderer)=0;
	};
}

#endif