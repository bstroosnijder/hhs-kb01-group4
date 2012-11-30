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
	 * @return	void
	 */
	DirectX9Renderer::~DirectX9Renderer()
	{
		CleanUp();
	}

	/**
	 * Clean the DirectX9Renderer object, releasing every Direct3D9 object associated with it.
	 * @return	void
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
	 */
	void DirectX9Renderer::Clear()
	{

	}

	/**
	 * Begins a scene.
	 * TODO more info
	 */
	void DirectX9Renderer::BeginScene()
	{

	}

	/**
	 * Ends a scene.
	 * TODO more info
	 */
	void DirectX9Renderer::EndScene()
	{

	}

	/**
	 * Presents stuff to the window.
	 * @param	window		The window to present the drawn data to.
	 * TODO more info
	 */
	void DirectX9Renderer::Present(Window* argWindow)
	{

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
	 */
	void DirectX9Renderer::SetFVF()
	{

	}

	/**
	 * Sets the stream source.
	 * TODO more info
	 */
	void DirectX9Renderer::SetStreamSource()
	{

	}
}