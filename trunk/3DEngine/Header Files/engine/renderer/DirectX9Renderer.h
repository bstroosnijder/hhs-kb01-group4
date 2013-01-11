#ifndef DIRECTX9RENDERER_H_
#define DIRECTX9RENDERER_H_

#include <Windows.h>
#include <d3dx9.h>
#include "..\logger\Logger.h"
#include "Renderer.h"
#include "..\input\InputListener.h"
#include "..\window\Win32Window.h"

namespace engine
{
	/**
	 * The DirectX9Renderer is responsible for providing a communication gateway towards the DirectX9 API.
	 */
	class DirectX9Renderer : public Renderer , public InputListener
	{
	private:
		LPDIRECT3D9 pDirect3d;
		LPDIRECT3DDEVICE9 pDevice;
		
		LPD3DXMATRIXSTACK matView;
		LPD3DXMATRIXSTACK matProjection;
	public:
		LPD3DXMATRIXSTACK matWorld;
		DirectX9Renderer(HWND argHWin);
		~DirectX9Renderer();
		void CleanUp();
		
		void* GetDevice();
		void SetupMatricis();

		bool CreateVertexBuffer(void* argPVertexBuffer, unsigned long argSize, unsigned long argStruct, void* argPVertices);
		bool CreateIndexBuffer(void* argPIndexBuffer, unsigned long argSize, short* argPIndices);
		
		void AddToWorldMatrix(void* argPMatrix);
		void TransformWorldMatrix();
		void TransformViewMatrix();
		void TransformProjectionMatrix();

		void Clear();
		void BeginScene();
		void Push();

		void SetStreamSource(void* argPVertexBuffer, unsigned long argSizePerVertex);
		void SetFVF(unsigned long argStruct);
		void SetIndices(void* argPIndexBuffer);
		
		void SetMaterial(void* argPMaterial);
		void SetTexture(unsigned long argIndex, void* argPTexture);

		void DrawPrimitive(unsigned long argPrimitiveType, unsigned long argNumPrimitives);
		void DrawIndexedPrimitive(unsigned long argPrimitiveType, unsigned long argNumVertices, unsigned long argNumPrimitives);

		void Pop();
		void EndScene();
		void Present(Window* argWindow);

		void InputEvent(std::string argBind, float argSpeed);
	};
}

#endif