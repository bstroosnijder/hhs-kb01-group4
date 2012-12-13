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
		D3DPRESENT_PARAMETERS presentParameters;
		pDirect3d = Direct3DCreate9(D3D_SDK_VERSION);
		ZeroMemory(&presentParameters, sizeof(presentParameters));

		presentParameters.Windowed = true;
		presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
		presentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
		presentParameters.EnableAutoDepthStencil = true;
		presentParameters.AutoDepthStencilFormat = D3DFMT_D16;
		presentParameters.BackBufferWidth = 800;
		presentParameters.BackBufferHeight = 600;

		this->pDirect3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, argHWin,
								D3DCREATE_SOFTWARE_VERTEXPROCESSING,
								&presentParameters, &pDevice);

		// Set render states
		this->pDevice->SetRenderState(D3DRS_ZENABLE, true);
		this->pDevice->SetRenderState(D3DRS_AMBIENT, 0xFFFFFFFF);
		this->pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		// Set matrices to the identity
		this->SetupMatricis();
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
		// Cleans the device
		if(this->pDevice != NULL)
		{
			this->pDevice->Release();
		}
		// Cleans the direct3d
		if(this->pDirect3d != NULL)
		{
			this->pDirect3d->Release();
		}

		// Cleans the world matrix stack
		if(this->matWorld != NULL)
		{
			this->matWorld->Release();
		}
		// Cleans the view matrix stack
		if(this->matView != NULL)
		{
			this->matView->Release();
		}
		// Cleans the projection matrix stack
		/*if(this->matProjection != NULL)
		{
			this->matProjection->Release();
		}*/
	}

	/**
	 * Set up the world matrix.
	 * TODO: More information.
	 * @return		void
	 */
	void DirectX9Renderer::SetupMatricis()
	{
		D3DXCreateMatrixStack(0, &this->matWorld);
		this->matWorld->LoadIdentity();

		D3DXCreateMatrixStack(0, &this->matView);
		this->matView->LoadIdentity();

		D3DXCreateMatrixStack(0, &this->matProjection);
		this->matProjection->LoadIdentity();
	}

	/**
	 * Clears the screen.
	 * TODO more info
	 * @return		void
	 */
	void DirectX9Renderer::Clear()
	{
		this->pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
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
	 * Pushes a new matrix on the stack
	 * @return		void
	 */
	void DirectX9Renderer::Push()
	{
		this->matWorld->Push();
		//this->matView->Push();
		//this->matProjection->Push();
	}
	
	/**
	 * Pops the last matrix off the stack
	 * @return		void
	 */
	void DirectX9Renderer::Pop()
	{
		this->matWorld->Pop();
		//this->matView->Pop();
		//this->matProjection->Pop();
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
	 * Getter for the grapics device
	 * @return		LPDIRECT3DDEVICE9
	 */
	LPDIRECT3DDEVICE9 DirectX9Renderer::GetDevice()
	{
		return this->pDevice;
	}

	/**
	 * Adds a new matrix to the world matrix via multiplication
	 * @return		void
	 */
	void DirectX9Renderer::AddToWorldMatrix(D3DXMATRIXA16* argPMatrix)
	{
		this->matWorld->MultMatrixLocal(argPMatrix);
	}

	/**
	 * Transforms the world matrix
	 * @return		void
	 */
	void DirectX9Renderer::TransformWorldMatrix()
	{
		this->pDevice->SetTransform(D3DTS_WORLD, this->matWorld->GetTop());
	}

	/**
	 * Transforms the view matrix
	 * @return		void
	 */
	void DirectX9Renderer::TransformViewMatrix()	
	{
		D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-10.0f );
		D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
		D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
		D3DXMatrixLookAtLH(this->matView->GetTop(), &vEyePt, &vLookatPt, &vUpVec);
		this->pDevice->SetTransform(D3DTS_VIEW, this->matView->GetTop());
	}

	/**
	 * Transforms the projection matrix
	 * @return		void
	 */
	void DirectX9Renderer::TransformProjectionMatrix()
	{
		D3DXMatrixPerspectiveFovLH(this->matProjection->GetTop(), D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
		this->pDevice->SetTransform(D3DTS_PROJECTION, this->matProjection->GetTop());
	}
}