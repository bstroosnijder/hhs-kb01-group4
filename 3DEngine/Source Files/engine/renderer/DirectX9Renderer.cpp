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
	DirectX9Renderer::DirectX9Renderer(HWND argHWin) : Renderer()
	{
		Logger::Log("DirectX9Renderer: Initializing", Logger::INFO, __FILE__, __LINE__);

		// Sets the light index to zero
		this->lightIndex							= 0;

		D3DPRESENT_PARAMETERS presentParameters;
		pDirect3d = Direct3DCreate9(D3D_SDK_VERSION);
		ZeroMemory(&presentParameters, sizeof(presentParameters));

		presentParameters.Windowed					= true;
		presentParameters.SwapEffect				= D3DSWAPEFFECT_DISCARD;
		presentParameters.BackBufferFormat			= D3DFMT_UNKNOWN;
		presentParameters.EnableAutoDepthStencil	= true;
		presentParameters.AutoDepthStencilFormat	= D3DFMT_D16;
		presentParameters.BackBufferWidth			= 800;
		presentParameters.BackBufferHeight			= 600;

		this->pDirect3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, argHWin,
								D3DCREATE_SOFTWARE_VERTEXPROCESSING,
								&presentParameters, &pDevice);

		// Set render states
		this->pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		this->pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		this->pDevice->SetRenderState(D3DRS_ZENABLE, true);
		this->pDevice->SetRenderState(D3DRS_LIGHTING, true);
		this->pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(100, 100, 100));
		this->pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
		
		// Set sampler states
		//this->pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		//this->pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		//this->pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

		// Global Lighting
		D3DLIGHT9 gLight;
		ZeroMemory(&gLight, sizeof(gLight));
		gLight.Type			= D3DLIGHT_DIRECTIONAL;
		gLight.Diffuse		= D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		gLight.Direction	= D3DXVECTOR3(-1.0f, -0.3f, -1.0f);
		this->pDevice->SetLight(0, &gLight);
		this->pDevice->LightEnable(0, true);

		// Global Material
		D3DMATERIAL9 gMaterial;
		ZeroMemory(&gMaterial, sizeof(gMaterial));
		gMaterial.Ambient	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		gMaterial.Diffuse	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		this->pDevice->SetMaterial(&gMaterial);

		// Set matrices to the identity
		this->SetupMatricis();

		Logger::Log("DirectX9Renderer: Finished", Logger::INFO, __FILE__, __LINE__);
	}

	/**
	 * Destructs the DirectX9Renderer object.
	 */
	DirectX9Renderer::~DirectX9Renderer()
	{
		Logger::Log("DirectX9Renderer: Disposing", Logger::INFO, __FILE__, __LINE__);
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
	 * Returns the current top of the world matrix stack
	 * @return		void*
	 */
	void* DirectX9Renderer::GetWorldTop()
	{
		return this->matWorld->GetTop();
	}

	/**
	 * Loads a matrix as the new world matrix
	 * @param		void*				The matrix to be the new world matrix
	 * @return		void
	 */
	void DirectX9Renderer::LoadWorldMatrix(void* argPMatrix)
	{
		D3DXMATRIXA16* pMatrix = (D3DXMATRIXA16*)argPMatrix;
		this->matWorld->LoadMatrix(pMatrix);
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
	 * Returns the current top of the view matrix stack
	 * @return		void*
	 */
	void* DirectX9Renderer::GetViewTop()
	{
		return this->matView->GetTop();
	}

	/**
	 * Adds a new matrix to the view matrix via multiplication
	 * @param		void*				The matrix to multiply the current view matrix with
	 * @return		void
	 */
	void DirectX9Renderer::AddToViewMatrix(void* argPMatrix)
	{
		D3DXMATRIXA16* pMatrix = (D3DXMATRIXA16*)argPMatrix;
		this->matView->MultMatrixLocal(pMatrix);
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
		//D3DXVECTOR3 vEyePt(0.0f, 0.0f, 0.0f);
		//D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 1.0f);
		//D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
		//D3DXMatrixLookAtLH(this->matView->GetTop(), &vEyePt, &vLookatPt, &vUpVec);
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
	 * Returns the next index for the light objects
	 * @return		unsigned long
	 */
	unsigned long DirectX9Renderer::GetNextLightIndex()
	{
		unsigned long curIndex = this->lightIndex;
		this->lightIndex++;
		return curIndex;
	}

	/**
	 * Sets a light struct in the given index
	 * @param		unsigned long		The index of the light struct
	 * @param		void*				A pointer to the light struct
	 * @return		void
	 */
	void DirectX9Renderer::SetLight(unsigned long argLightIndex, void* argPLight)
	{
		D3DLIGHT9* pLight = (D3DLIGHT9*)argPLight;
		this->pDevice->SetLight(argLightIndex, pLight);
	}

	/**
	 * Enables the light at the given index
	 * @param		unsigned long		The index of the light struct
	 * @param		bool				A bool to indicate the status of the light
	 * @return		void
	 */
	void DirectX9Renderer::LightEnable(unsigned long argLightIndex, bool argEnable)
	{
		this->pDevice->LightEnable(argLightIndex, argEnable);
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
		this->matProjection->Push();
	}

	/**
	 * Sets the stream to the given vertex buffer
	 * @param		void*				The vertex buffer to use
	 * @param		unsigned long		The size of a single vertex in the buffer
	 * @return		void
	 */
	void DirectX9Renderer::SetStreamSource(void* argPVertexBuffer, unsigned long argSizePerVertex)
	{
		LPDIRECT3DVERTEXBUFFER9 pVertexBuffer	= (LPDIRECT3DVERTEXBUFFER9)argPVertexBuffer;
		this->pDevice->SetStreamSource(0, pVertexBuffer, 0, argSizePerVertex);
	}
	
	/**
	 * Sets The FVF to use for the next thing that comes throu the pipeline
	 * @param		unsigned long		The FVF to use
	 * @return		void
	 */
	void DirectX9Renderer::SetFVF(unsigned long argStruct)
	{
		this->pDevice->SetFVF(argStruct);
	}

	/**
	 * Sets the index buffer to use with a vertex buffer
	 * @param		void*				The vertex buffer to use
	 * @return		void
	 */
	void DirectX9Renderer::SetIndices(void* argPIndexBuffer)
	{
		LPDIRECT3DINDEXBUFFER9 pIndexBuffer	= (LPDIRECT3DINDEXBUFFER9)argPIndexBuffer;
		this->pDevice->SetIndices(pIndexBuffer);
	}

	/**
	 * Sets a material to use on the current pipeline
	 * @param		void*				The material to use
	 * @return		void
	 */
	void DirectX9Renderer::SetMaterial(void* argPMaterial)
	{
		D3DMATERIAL9* pMaterial				= (D3DMATERIAL9*)argPMaterial;
		this->pDevice->SetMaterial(pMaterial);
	}

	/**
	 * Sets a texture to use on the current pipeline
	 * @param		unsigned long		The index of the texture
	 * @param		void*				The texture to use
	 * @return		void
	 */
	void DirectX9Renderer::SetTexture(unsigned long argIndex, void* argPTexture)
	{
		LPDIRECT3DTEXTURE9 pTexture			= (LPDIRECT3DTEXTURE9)argPTexture;
		this->pDevice->SetTexture(argIndex, pTexture);
	}

	/**
	 * Draws the current pipeline as a primitive
	 * @param		unsigned long		The primitive type
	 * @param		unsigned long		The number of primitives to draw
	 * @return		void
	 */
	void DirectX9Renderer::DrawPrimitive(unsigned long argPrimitiveType, unsigned long argNumPrimitives)
	{
		D3DPRIMITIVETYPE primitiveType		= (D3DPRIMITIVETYPE)argPrimitiveType;
		this->pDevice->DrawPrimitive(primitiveType, 0, argNumPrimitives);
	}

	/**
	 * Draws the current pipeline as an indexed primitive
	 * @param		unsigned long		The primitive type
	 * @param		unsigned long		The number of vertices in the vertex buffer
	 * @param		unsigned long		The number of primitives to draw
	 * @return		void
	 */
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
		this->matProjection->Pop();
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
	
	/**
	 * Processes any input events
	 * @param		std::string		the bind to execute
	 * @param		float			the speed
	 * @return		void
	 */
	void DirectX9Renderer::InputEvent(std::string argBind, float argSpeed)
	{
		if(argBind == "light_false")
		{
				this->pDevice->SetRenderState(D3DRS_LIGHTING, false);
		}
		else if(argBind == "light_true")
		{
				this->pDevice->SetRenderState(D3DRS_LIGHTING, true);
		}
		else if(argBind == "fill_solid")
		{
			this->pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
		else if(argBind == "fill_wireframe")
		{
			this->pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		}
		else if(argBind == "cull_ccw")
		{
			this->pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		}
		else if(argBind == "cull_cw")
		{
			this->pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
		}
		else if(argBind == "cull_none")
		{
			this->pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		}
		else if(argBind == "clight")
		{
			unsigned long colorRGB = (unsigned long)(argSpeed * 255);
			this->pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(colorRGB, colorRGB, colorRGB));
		}
	}
}