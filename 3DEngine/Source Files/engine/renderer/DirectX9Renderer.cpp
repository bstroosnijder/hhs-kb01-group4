#include "..\..\..\Header Files\engine\renderer\DirectX9Renderer.h"

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
		Logger::Log("DirectX9Renderer: Initializing", Logger::INFO, __FILE__, __LINE__);

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
		this->pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		this->pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		this->pDevice->SetRenderState(D3DRS_ZENABLE, true);
		this->pDevice->SetRenderState(D3DRS_LIGHTING, false);
		//this->pDevice->SetRenderState(D3DRS_AMBIENT, 0xFFFFFFFF);
		
		this->pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		this->pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		this->pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

		// Set matrices to the identity
		this->SetupMatricis();

		Logger::Log("DirectX9Renderer: Finished", Logger::INFO, __FILE__, __LINE__);
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
		if(this->matProjection != NULL)
		{
			this->matProjection->Release();
		}
	}

	/**
	 * Getter for the grapics device
	 * @return		void*
	 */
	void* DirectX9Renderer::GetDevice()
	{
		return this->pDevice;
	}

	/**
	 * Set up the world, view and projection matrix stacks and loads an identity matrix in the top of all 3.
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
	 * Creates a vertex buffer and copies the data to the memory
	 * @param		void*				The vertex buffer itself
	 * @param		unsigned long		The size of the memory to reserve
	 * @param		unsigned long		The struct representing one vertex
	 * @param		void*				The array of vertices
	 * @return		bool
	 */
	bool DirectX9Renderer::CreateVertexBuffer(void* argPVertexBuffer, unsigned long argSize, unsigned long argStruct, void* argPVertices)
	{
		LPDIRECT3DVERTEXBUFFER9* pVertexBuffer	= (LPDIRECT3DVERTEXBUFFER9*)argPVertexBuffer;
		if(pVertexBuffer == NULL)
		{
			Logger::Log("DirectX9Renderer: Vertex buffer is wrong", Logger::FATAL, __FILE__, __LINE__);
			return false;
		}

		this->pDevice->CreateVertexBuffer(argSize, 0, argStruct, D3DPOOL_DEFAULT, pVertexBuffer, NULL);

		void* pVoid;
		(*pVertexBuffer)->Lock(0, argSize, (void**)&pVoid, 0);
		memcpy(pVoid, argPVertices, argSize);
		(*pVertexBuffer)->Unlock();

		return true;
	}

	/**
	 * Creates a index buffer and copies the data to the memory
	 * @param		void*				The index buffer itself
	 * @param		unsigned long		The size of the memory to reserve
	 * @param		void*				The array of indices
	 * @return		bool
	 */
	bool DirectX9Renderer::CreateIndexBuffer(void* argPIndexBuffer, unsigned long argSize, short* argPIndices)
	{
		LPDIRECT3DINDEXBUFFER9* pIndexBuffer	= (LPDIRECT3DINDEXBUFFER9*)argPIndexBuffer;
		if(pIndexBuffer == NULL)
		{
			Logger::Log("DirectX9Renderer: Index buffer is wrong", Logger::FATAL, __FILE__, __LINE__);
			return false;
		}

		this->pDevice->CreateIndexBuffer(argSize, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, (IDirect3DIndexBuffer9**)argPIndexBuffer, NULL);

		void* pVoid;
		(*pIndexBuffer)->Lock(0, argSize, (void**)&pVoid, 0);
		memcpy(pVoid, argPIndices, argSize);
		(*pIndexBuffer)->Unlock();

		return true;
	}

	/**
	 * Adds a new matrix to the world matrix via multiplication
	 * @param		void*				The matrix to multiply the current world matrix with
	 * @return		void
	 */
	void DirectX9Renderer::AddToWorldMatrix(void* argPMatrix)
	{
		D3DXMATRIXA16* pMatrix = (D3DXMATRIXA16*)argPMatrix;
		this->matWorld->MultMatrixLocal(pMatrix);
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
		D3DXVECTOR3 vEyePt(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 1.0f);
		D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
		D3DXMatrixLookAtLH(this->matView->GetTop(), &vEyePt, &vLookatPt, &vUpVec);
		this->pDevice->SetTransform(D3DTS_VIEW, this->matView->GetTop());
	}

	/**
	 * Transforms the projection matrix
	 * @return		void
	 */
	void DirectX9Renderer::TransformProjectionMatrix()
	{
		D3DXMatrixPerspectiveFovLH(this->matProjection->GetTop(), (D3DX_PI / 4), 1.0f, 1.0f, 200.0f);
		this->pDevice->SetTransform(D3DTS_PROJECTION, this->matProjection->GetTop());
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
		this->matView->Push();
		//this->matProjection->Push();
	}

	void DirectX9Renderer::SetStreamSource(void* argPVertexBuffer, unsigned long argSizePerVertex)
	{
		LPDIRECT3DVERTEXBUFFER9 pVertexBuffer	= (LPDIRECT3DVERTEXBUFFER9)argPVertexBuffer;
		this->pDevice->SetStreamSource(0, pVertexBuffer, 0, argSizePerVertex);
	}

	void DirectX9Renderer::SetFVF(unsigned long argStruct)
	{
		this->pDevice->SetFVF(argStruct);
	}

	void DirectX9Renderer::SetIndices(void* argPIndexBuffer)
	{
		LPDIRECT3DINDEXBUFFER9 pIndexBuffer	= (LPDIRECT3DINDEXBUFFER9)argPIndexBuffer;
		this->pDevice->SetIndices(pIndexBuffer);
	}

	void DirectX9Renderer::SetMaterial(void* argPMaterial)
	{
		D3DMATERIAL9* pMaterial				= (D3DMATERIAL9*)argPMaterial;
		this->pDevice->SetMaterial(pMaterial);
	}

	void DirectX9Renderer::SetTexture(unsigned long argIndex, void* argPTexture)
	{
		LPDIRECT3DTEXTURE9 pTexture			= (LPDIRECT3DTEXTURE9)argPTexture;
		this->pDevice->SetTexture(argIndex, pTexture);
	}

	void DirectX9Renderer::DrawPrimitive(unsigned long argPrimitiveType, unsigned long argNumPrimitives)
	{
		D3DPRIMITIVETYPE primitiveType		= (D3DPRIMITIVETYPE)argPrimitiveType;
		this->pDevice->DrawPrimitive(primitiveType, 0, argNumPrimitives);
	}

	void DirectX9Renderer::DrawIndexedPrimitive(unsigned long argPrimitiveType, unsigned long argNumVertices, unsigned long argNumPrimitives)
	{
		D3DPRIMITIVETYPE primitiveType		= (D3DPRIMITIVETYPE)argPrimitiveType;
		this->pDevice->DrawIndexedPrimitive(primitiveType, 0, 0, argNumVertices, 0, argNumPrimitives);
	}
	
	/**
	 * Pops the last matrix off the stack
	 * @return		void
	 */
	void DirectX9Renderer::Pop()
	{
		this->matWorld->Pop();
		this->matView->Pop();
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
	 * @param		window*				The window to present the drawn data to.
	 * @return		void
	 */
	void DirectX9Renderer::Present(Window* argPWindow)
	{
		Win32Window* window = (Win32Window*)argPWindow;
		this->pDevice->Present(NULL, NULL, window->GetHWin(), NULL);
	}

	void DirectX9Renderer::InputEvent(std::string argBind, float argSpeed)
	{
		if(argBind == "toggle_wireframe")
		{
			unsigned long renderState;
			this->pDevice->GetRenderState(D3DRS_FILLMODE, &renderState);
			if (renderState == D3DFILL_SOLID)
			{
				this->pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			}
			else
			{
				this->pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			}
		}
	}
}