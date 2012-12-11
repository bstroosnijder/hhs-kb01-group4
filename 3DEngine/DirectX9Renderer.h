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

		D3DXMATRIXA16 matWorld;
		D3DXMATRIXA16 matView;
		D3DXMATRIXA16 matProjection;
	public:
		static const int LOG_LEVEL_INFO;
		static const int LOG_LEVEL_WARNING;

		DirectX9Renderer(HWND argHWin);
		~DirectX9Renderer();
		void CleanUp();

		void SetupMatricis();

		void Clear();
		void BeginScene();
		void EndScene();
		void Present(Window* argWindow);

		// todo: Are these still needed?
		void SetStreamSource();
		void SetFVF();
		void DrawPrimitive();
		// i think not!

		// todo: can we make this nicer?
		LPDIRECT3DDEVICE9 GetDevice();

		void AddToWorldMatrix(D3DXMATRIXA16* argPMatrix);
		void TransformWorldMatrix();
		void TransformViewMatrix();
		void TransformProjectionMatrix();
	};
}

#endif