#include "..\..\..\..\Header Files\engine\scene\entities\Skybox.h"

namespace engine
{
	Skybox::Skybox() : Entity()
	{
		Logger::Log("Skybox: Initializing", Logger::INFO, __FILE__, __LINE__);
		Logger::Log("Skybox: Finished", Logger::INFO, __FILE__, __LINE__);
	}

	Skybox::~Skybox()
	{
		Logger::Log("Skybox: Disposing", Logger::INFO, __FILE__, __LINE__);
		this->CleanUp();
	}

	void Skybox::CleanUp()
	{
		if(this->pVertexBuffer != NULL)
		{
			this->pVertexBuffer->Release();
		}

		if(this->pIndexBuffer != NULL)
		{
			this->pIndexBuffer->Release();
		}
	}
	
	void Skybox::SetupVertices(Renderer* argPRenderer)
	{
		float boxSize					= 1.5f;

		unsigned long numVertices = 8;
		unsigned long vertexArraySize	= numVertices * sizeof(TexturedVector3);
		TexturedVector3 vertices[]		=
		{
			// Front Top Left
			{-boxSize, boxSize, boxSize, 0xFFCCCCCC, 1.0f, 0.0f },
			// Front Top Right
			{ boxSize, boxSize, boxSize, 0xFFCCCCCC, 0.0f, 0.0f },
			// Front Bottom Left
			{-boxSize,-boxSize, boxSize, 0xFFCCCCCC, 1.0f, 1.0f },
			// Front Bottom Right
			{ boxSize,-boxSize, boxSize, 0xFFCCCCCC, 0.0f, 1.0f },

			// Back Top Left
			{-boxSize, boxSize,-boxSize, 0xFFCCCCCC, 0.0f, 0.0f },
			// Back Top Right
			{ boxSize, boxSize,-boxSize, 0xFFCCCCCC, 1.0f, 0.0f },
			// Back Bottom Left
			{-boxSize,-boxSize,-boxSize, 0xFFCCCCCC, 0.0f, 1.0f },
			// Back Bottom Right
			{ boxSize,-boxSize,-boxSize, 0xFFCCCCCC, 1.0f, 1.0f }
		};
		
		unsigned long indexArraySize	= 36 * sizeof(short);
		short indices[]					=
		{
			// Front
			0, 2, 1,
			3, 1, 2,

			// Back
			5, 7, 4,
			6, 4, 7,

			// Left
			4, 6, 0,
			2, 0, 6,

			// Right
			1, 3, 5,
			7, 5, 3,

			// Top
			4, 0, 5,
			1, 5, 0,

			// Bottom
			2, 6, 3,
			7, 3, 6
		};

		// Create the vertex buffer
		argPRenderer->CreateVertexBuffer(&this->pVertexBuffer, vertexArraySize, D3DFVFTexturedVector3, vertices);

		// Create the index buffer
		argPRenderer->CreateIndexBuffer(&this->pIndexBuffer, indexArraySize, indices);
	}

	void Skybox::Update()
	{
	}

	void Skybox::Draw(Renderer* argPRenderer)
	{
		DirectX9Renderer* pRenderer = (DirectX9Renderer*)argPRenderer;
		D3DXMatrixIdentity(&this->matWorld);
		D3DXMatrixMultiply(&this->matWorld, pRenderer->matWorld->GetTop(), &this->matWorld);

		D3DXVECTOR3 vecScale;
		D3DXQUATERNION quatRotation;
		D3DXVECTOR3 vecTranslation;
		D3DXMatrixDecompose(&vecScale, &quatRotation, &vecTranslation, &this->matWorld);

		D3DXMATRIXA16 matTranslation;
		D3DXMatrixTranslation(&matTranslation, vecTranslation.x, vecTranslation.y, vecTranslation.z);
		D3DXMatrixInverse(&matTranslation, NULL, &matTranslation);
		D3DXMatrixMultiply(&this->matWorld, &this->matWorld, &matTranslation);

		pRenderer->matWorld->LoadMatrix(&this->matWorld);

		// Apply the matrix transformations
		argPRenderer->TransformWorldMatrix();
		argPRenderer->TransformViewMatrix();
		argPRenderer->TransformProjectionMatrix();

		// Turn of the Z axis
		LPDIRECT3DDEVICE9 pDevice = (LPDIRECT3DDEVICE9)argPRenderer->GetDevice();
		pDevice->SetRenderState(D3DRS_ZENABLE, false);

		argPRenderer->SetStreamSource(this->pVertexBuffer, sizeof(TexturedVector3));
		argPRenderer->SetIndices(this->pIndexBuffer);
		argPRenderer->SetFVF(D3DFVFTexturedVector3);
		argPRenderer->SetTexture(0, this->textures[0]);
		argPRenderer->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 8, 12);

		pDevice->SetRenderState(D3DRS_ZENABLE, true);
	}
	
	/**
	 * Sets a texture at a given index
	 * @param		unsigned long			The index to place the texture at
	 * @param		LPDIRECT3DTEXTURE9		The texture to draw on the giving index
	 * @return		void
	 */
	void Skybox::SetTexture(unsigned long argIndex, LPDIRECT3DTEXTURE9 argTexture)
	{
		this->textures[argIndex] = argTexture;
	}
}