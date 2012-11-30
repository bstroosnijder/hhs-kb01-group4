#ifndef RENDERER_H_
#define RENDERER_H_

#include "Window.h"

namespace engine
{
	/**
	 * Something about the renderer interface here.
	 */
	class Renderer
	{
	public:
		virtual void Clear()=0;
		virtual void BeginScene()=0;
		virtual void EndScene()=0;
		virtual void Present(Window* argWindow)=0;
	};
}

#endif