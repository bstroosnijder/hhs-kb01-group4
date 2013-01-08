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
			0, 1, 2,
			3, 2, 1,

			// Back
			5, 4, 7,
			6, 7, 4,

			// Left
			4, 0, 6,
			2, 6, 0,

			// Right
			1, 5, 3,
			7, 3, 5,

			// Top
			4, 5, 0,
			1, 0, 5,

			// Bottom
			2, 3, 6,
			7, 6, 3,
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
		// Reset the actual world matrxi again
		D3DXMatrixIdentity(&this->matWorld);

		// Scaling
		D3DXMATRIXA16 matScaling;
		D3DXMatrixScaling(&matScaling, this->scaling.x, this->scaling.y, this->scaling.z);
		D3DXMatrixMultiply(&this->matWorld, &this->matWorld, &matScaling);

		// Rotation X
		D3DXMATRIXA16 matRotationX;
		D3DXMatrixRotationX(&matRotationX, this->rotation.x);
		D3DXMatrixMultiply(&this->matWorld, &this->matWorld, &matRotationX);
		// Rotation Y
		D3DXMATRIXA16 matRotationY;
		D3DXMatrixRotationY(&matRotationY, this->rotation.y);
		D3DXMatrixMultiply(&this->matWorld, &this->matWorld, &matRotationY);
		// Rotation Z
		D3DXMATRIXA16 matRotationZ;
		D3DXMatrixRotationZ(&matRotationZ, this->rotation.z);
		D3DXMatrixMultiply(&this->matWorld, &this->matWorld, &matRotationZ);


		D3DXMatrixMultiply(&this->matWorld, pRenderer->matWorld->GetTop(), &this->matWorld);

		D3DXVECTOR3 vecScale;
		D3DXQUATERNION quatRotation;
		D3DXVECTOR3 vecTranslation;
		// Decompose the current world matrix, we need this so we counter camera movement and keep the skybox still
		D3DXMatrixDecompose(&vecScale, &quatRotation, &vecTranslation, &this->matWorld);
		
		// Position
		D3DXMATRIXA16 matTranslation;
		D3DXMatrixTranslation(&matTranslation, (vecTranslation.x + this->position.x), (vecTranslation.y + this->position.y), (vecTranslation.z + this->position.z));
		D3DXMatrixInverse(&matTranslation, NULL, &matTranslation);
		D3DXMatrixMultiply(&this->matWorld, &this->matWorld, &matTranslation);

		pRenderer->matWorld->LoadMatrix(&this->matWorld);

		// Apply the matrix transformations
		argPRenderer->TransformWorldMatrix();
		argPRenderer->TransformViewMatrix();
		argPRenderer->TransformProjectionMatrix();

		LPDIRECT3DDEVICE9 pDevice = (LPDIRECT3DDEVICE9)argPRenderer->GetDevice();
		// Turn of the Z axis
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