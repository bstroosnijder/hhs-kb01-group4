#ifndef RENDERER_H_
#define RENDERER_H_

#include "Window.h"

namespace engine
{
	/**
	 * The interface renderer serves as an abstraction for the different video driver API's.
	 */
	class Renderer
	{
	public:
		static const int DIRECTX_9_RENDERER;
		static const int OPEN_GL_RENDERER;
		
		virtual void SetupMatricis()=0;

		virtual void Clear()=0;
		virtual void BeginScene()=0;
		virtual void EndScene()=0;
		virtual void Present(Window* argWindow)=0;

		virtual void SetStreamSource()=0;
		virtual void SetFVF()=0;
		virtual void DrawPrimitive()=0;
	};
}

#endif