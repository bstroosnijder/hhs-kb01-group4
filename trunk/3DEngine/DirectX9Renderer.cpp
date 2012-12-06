#include "DirectX9Renderer.h"

struct CUSTOMVERTEX
{
    float x, y, z;
    unsigned long color;
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

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

		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		pDevice->SetRenderState(D3DRS_LIGHTING, false);

		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		// testing
		
    // Initialize three vertices for rendering a triangle
    CUSTOMVERTEX g_Vertices[] =
    {
		{  0.0f, 1.0f, 0.0f, 0xFFFF0000 },
		{ -1.0f,-1.0f, 0.0f, 0xFFFF0000 },
		{  1.0f,-1.0f, 0.0f, 0xFFFF0000 },
    };

    // Create the vertex buffer.
	this->pDevice->CreateVertexBuffer( 3 * sizeof( CUSTOMVERTEX ),
        0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &this->pVertexBuffer, NULL );

    // Fill the vertex buffer.
    VOID* pVertices;
	this->pVertexBuffer->Lock( 0, sizeof( g_Vertices ), ( void** )&pVertices, 0 );
    memcpy( pVertices, g_Vertices, sizeof( g_Vertices ) );
	this->pVertexBuffer->Unlock();
	}

	/**
	 * Destructs the DirectX9Renderer object.
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
	 * Calls upon the directx device to begin a scene.
	 * This is necessary for the directx's API to help it do magic.
	 * @return		void
	 */
	void DirectX9Renderer::BeginScene()
	{
		this->pDevice->BeginScene();
	}

	/**
	 * Set up the world matrix.
	 * TODO: More information.
	 * @return		void
	 */
	void DirectX9Renderer::SetupWorldMatrix()
	{
		D3DXMATRIXA16 matWorld;
		unsigned long iTime = timeGetTime() % 1000;
		float fAngle = iTime * ( 2.0f * D3DX_PI ) / 1000.0f;
		D3DXMatrixRotationY( &matWorld, fAngle );
		this->pDevice->SetTransform( D3DTS_WORLD, &matWorld );
	}
	
	/**
	 * Set up the view matrix.
	 * TODO: More information.
	 * @return		void
	 */
	void DirectX9Renderer::SetupViewMatrix()
	{
		D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );
		D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
		D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
		D3DXMATRIXA16 matView;
		D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
		this->pDevice->SetTransform( D3DTS_VIEW, &matView );
	}

	/**
	 * Set up the projection matrix.
	 * TODO: More information.
	 * @return		void
	 */
	void DirectX9Renderer::SetupProjectionMatrix()
	{
		D3DXMATRIXA16 matProj;
		D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f );
		this->pDevice->SetTransform( D3DTS_PROJECTION, &matProj );
	}

	/**
	 * Ends a scene.
	 * Calls upon the directx device to end a scene.
	 * This is necessary for the directx's API to help it do magic.
	 */
	void DirectX9Renderer::EndScene()
	{
		this->pDevice->EndScene();
	}

	/**
	 * Presents the handled entities to the window.
	 * @param		window		The window to present the drawn data to.
	 * @return		void
	 */
	void DirectX9Renderer::Present(Window* argPWindow)
	{
		Win32Window* window = (Win32Window*)argPWindow;
		this->pDevice->Present(NULL, NULL, window->GetHWin(), NULL);
	}

	/**
	 * Sets the stream source.
	 * TODO: More information.
	 * @return		void
	 */
	void DirectX9Renderer::SetStreamSource()
	{
		this->pDevice->SetStreamSource( 0, this->pVertexBuffer, 0, sizeof( CUSTOMVERTEX ) );
	}

	/**
	 * Sets the Flexible Vertex Format.
	 * TODO: More information.
	 * @return		void
	 */
	void DirectX9Renderer::SetFVF()
	{
		this->pDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
	}

	/**
	 * Draws a primitive figure.
	 * @return		void
	 */
	void DirectX9Renderer::DrawPrimitive()
	{
		this->pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 1 );
	}
}