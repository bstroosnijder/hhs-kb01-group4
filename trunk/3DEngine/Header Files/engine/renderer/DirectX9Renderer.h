#ifndef DIRECTX9RENDERER_H_
#define DIRECTX9RENDERER_H_

#include <Windows.h>
#include <d3dx9.h>
#include "Renderer.h"
#include "..\window\Win32Window.h"

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
		
		LPD3DXMATRIXSTACK matWorld;
		LPD3DXMATRIXSTACK matView;
		LPD3DXMATRIXSTACK matProjection;
	public:
		DirectX9Renderer(HWND argHWin);
		~DirectX9Renderer();
		void CleanUp();

		void SetupMatricis();

		void Clear();
		void BeginScene();
		void Push();
		void Pop();
		void EndScene();
		void Present(Window* argWindow);

		// todo: can we make this nicer?
		LPDIRECT3DDEVICE9 GetDevice();

		void AddToWorldMatrix(D3DXMATRIXA16* argPMatrix);
		void TransformWorldMatrix();
		void TransformViewMatrix();
		void TransformProjectionMatrix();
	};
}

#endif