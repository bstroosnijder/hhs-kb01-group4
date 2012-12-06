#ifndef DIRECTX9RENDERER_H_
#define DIRECTX9RENDERER_H_

#include <d3dx9.h>
#include <Windows.h>
#include "Renderer.h"
#include "Win32Window.h"

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
		static const int LOG_LEVEL_INFO;
		static const int LOG_LEVEL_WARNING;

		DirectX9Renderer(HWND argHWin);
		~DirectX9Renderer();

		void CleanUp();
		void Clear();
		void BeginScene();
		void SetupWorldMatrix();
		void SetupViewMatrix();
		void SetupProjectionMatrix();
		void EndScene();
		void Present(Window* argWindow);
		void SetStreamSource();
		void SetFVF();
		void DrawPrimitive();
	};
}

#endif