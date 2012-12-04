#include "DirectX9Renderer.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Construct the DirectX9Renderer object.
	 */
	DirectX9Renderer::DirectX9Renderer(HWND argHWin)
	{
		pDirect3d = Direct3DCreate9(D3D_SDK_VERSION);
		ZeroMemory(&presentParameters, sizeof(presentParameters));

		presentParameters.Windowed = true;
		presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
		presentParameters.BackBufferFormat = D3DFMT_UNKNOWN;

		pDirect3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, argHWin,
								D3DCREATE_SOFTWARE_VERTEXPROCESSING,
								&presentParameters, &pDevice);

		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		pDevice->SetRenderState(D3DRS_LIGHTING, false);

		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	/**
	 * Destruct the DirectX9Renderer object.
	 * @return		void
	 */
	DirectX9Renderer::~DirectX9Renderer()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void DirectX9Renderer::CleanUp()
	{
		if(pVertexBuffer != NULL)
		{
			pVertexBuffer->Release();
		}
		if(pDevice != NULL)
		{
			pDevice->Release();
		}
		if(pDirect3d != NULL)
		{
			pDirect3d->Release();
		}
	}

	/**
	 * Clears the screen.
	 * TODO more info
	 * @return		void
	 */
	void DirectX9Renderer::Clear()
	{
		this->pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	}

	/**
	 * Begins a scene.
	 * TODO more info
	 * @return		void
	 */
	void DirectX9Renderer::BeginScene()
	{
		this->pDevice->BeginScene();
	}

	void DirectX9Renderer::SetupWorldMatrix()
	{
		D3DXMATRIXA16 matWorld;
		this->pDevice->SetTransform( D3DTS_WORLD, &matWorld );
	}
	
	void DirectX9Renderer::SetupViewMatrix()
	{
		D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );
		D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
		D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
		D3DXMATRIXA16 matView;
		D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
		this->pDevice->SetTransform( D3DTS_VIEW, &matView );
	}

	void DirectX9Renderer::SetupProjectionMatrix()
	{
		D3DXMATRIXA16 matProj;
		D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f );
		this->pDevice->SetTransform( D3DTS_PROJECTION, &matProj );
	}

	/**
	 * Ends a scene.
	 * TODO more info
	 * @return		void
	 */
	void DirectX9Renderer::EndScene()
	{
		this->pDevice->EndScene();
	}

	/**
	 * Presents stuff to the window.
	 * @param		window		The window to present the drawn data to.
	 * TODO more info
	 * @return		void
	 */
	void DirectX9Renderer::Present(Window* argPWindow)
	{
		Win32Window* window = (Win32Window*)argPWindow;
		this->pDevice->Present(NULL, NULL, window->GetHWin(), NULL);
	} 

	/**
	 * Draws a primitive figure.
	 * TODO more info
	 */
	void DirectX9Renderer::DrawPrimitive()
	{
	}

	/**
	 * Sets the FVF.
	 * TODO more info
	 * @return		void
	 */
	void DirectX9Renderer::SetFVF()
	{
	}

	/**
	 * Sets the stream source.
	 * TODO more info
	 * @return		void
	 */
	void DirectX9Renderer::SetStreamSource()
	{
	}
}