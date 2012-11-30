#ifndef DIRECTX9RENDERER_H_
#define DIRECTX9RENDERER_H_

#include "Renderer.h"
#include "Win32Window.h"
#include <d3d9.h>

namespace engine
{
	/**
	 * The DirectX9Renderer is responsible for providing a communication gateway towards the DirectX9 API.
	 */
	class DirectX9Renderer : public Renderer
	{
	private:
		LPDIRECT3D9 pDirect3d;
		LPDIRECT3DDEVICE9 pDevice;
		LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
		D3DPRESENT_PARAMETERS presentParameters;
	public:
		DirectX9Renderer(HWND argHWin);
		~DirectX9Renderer();

		void CleanUp();
		void Clear();
		void BeginScene();
		void EndScene();
		void Present(Window* argWindow);
		void DrawPrimitive();
		void SetFVF();
		void SetStreamSource();
	};
}

#endif