#include "..\..\..\..\Header Files\engine\scene\entities\Skybox.h"

namespace engine
{
	/**
	 * Construct the Skybox object.
	 */
	Skybox::Skybox() : Entity()
	{
		Logger::Log("Skybox: Initializing", Logger::INFO, __FILE__, __LINE__);
		Logger::Log("Skybox: Finished", Logger::INFO, __FILE__, __LINE__);
	}

	/**
	 * Destructs the Skybox object.
	 */
	Skybox::~Skybox()
	{
		Logger::Log("Skybox: Disposing", Logger::INFO, __FILE__, __LINE__);
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
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
	
	/**
	 * Sets up the vertices and indices within those vertices to properly setup the skybox.
	 * Vertices created this way are stored inside the private indexbuffer and vertexbuffer for later potential manipulation and usage.
	 * @param		Renderer*			A pointer to the renderer used to render the vertices.
	 * @return		void
	 */
	void Skybox::SetupVertices(Renderer* argPRenderer)
	{
		float boxSize					= 2.0f;

		// 8 vertices for a cube, and 3 per corner of the cube.
		unsigned long numVertices = 8 * 3;
		unsigned long vertexArraySize	= numVertices * sizeof(TexturedVector3);
		TexturedVector3 vertices[]		=
		{
			// (00) Front Top Left
			{-boxSize, boxSize, boxSize, D3DXVECTOR3( 0.0f, 0.0f,-1.0f), 0.0f, 0.0f },
			// (01) Front Top Right
			{ boxSize, boxSize, boxSize, D3DXVECTOR3( 0.0f, 0.0f,-1.0f), 1.0f, 0.0f },
			// (02) Front Bottom Left
			{-boxSize,-boxSize, boxSize, D3DXVECTOR3( 0.0f, 0.0f,-1.0f), 0.0f, 1.0f },
			// (03) Front Bottom Right
			{ boxSize,-boxSize, boxSize, D3DXVECTOR3( 0.0f, 0.0f,-1.0f), 1.0f, 1.0f },

			// (04) Back Top Left
			{-boxSize, boxSize,-boxSize, D3DXVECTOR3( 0.0f, 0.0f, 1.0f), 1.0f, 0.0f },
			// (05) Back Top Right
			{ boxSize, boxSize,-boxSize, D3DXVECTOR3( 0.0f, 0.0f, 1.0f), 0.0f, 0.0f },
			// (06) Back Bottom Left
			{-boxSize,-boxSize,-boxSize, D3DXVECTOR3( 0.0f, 0.0f, 1.0f), 1.0f, 1.0f },
			// (07) Back Bottom Right
			{ boxSize,-boxSize,-boxSize, D3DXVECTOR3( 0.0f, 0.0f, 1.0f), 0.0f, 1.0f },

			// (08) Left Top Left
			{-boxSize, boxSize,-boxSize, D3DXVECTOR3( 1.0f, 0.0f, 0.0f), 0.0f, 0.0f },
			// (09) Left Top Right
			{-boxSize, boxSize, boxSize, D3DXVECTOR3( 1.0f, 0.0f, 0.0f), 1.0f, 0.0f },
			// (10) Left Bottom Left
			{-boxSize,-boxSize,-boxSize, D3DXVECTOR3( 1.0f, 0.0f, 0.0f), 0.0f, 1.0f },
			// (11) Left Bottom Right
			{-boxSize,-boxSize, boxSize, D3DXVECTOR3( 1.0f, 0.0f, 0.0f), 1.0f, 1.0f },

			// (12) Right Top Left
			{ boxSize, boxSize, boxSize, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 0.0f, 0.0f },
			// (13) Right Top Right
			{ boxSize, boxSize,-boxSize, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 1.0f, 0.0f },
			// (14) Right Bottom Left
			{ boxSize,-boxSize, boxSize, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 0.0f, 1.0f },
			// (15) Right Bottom Right
			{ boxSize,-boxSize,-boxSize, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 1.0f, 1.0f },

			// (16) Top Top Left
			{-boxSize, boxSize,-boxSize, D3DXVECTOR3( 0.0f,-1.0f, 0.0f), 0.0f, 0.0f },
			// (17) Top Top Right
			{ boxSize, boxSize,-boxSize, D3DXVECTOR3( 0.0f,-1.0f, 0.0f), 1.0f, 0.0f },
			// (18) Top Bottom Left
			{-boxSize, boxSize, boxSize, D3DXVECTOR3( 0.0f,-1.0f, 0.0f), 0.0f, 1.0f },
			// (19) Top Bottom Right
			{ boxSize, boxSize, boxSize, D3DXVECTOR3( 0.0f,-1.0f, 0.0f), 1.0f, 1.0f },

			// (20) Bottom Top Left
			{-boxSize,-boxSize, boxSize, D3DXVECTOR3( 0.0f, 1.0f, 0.0f), 0.0f, 0.0f },
			// (21) Bottom Top Right
			{ boxSize,-boxSize, boxSize, D3DXVECTOR3( 0.0f, 1.0f, 0.0f), 1.0f, 0.0f },
			// (22) Bottom Bottom Left
			{-boxSize,-boxSize,-boxSize, D3DXVECTOR3( 0.0f, 1.0f, 0.0f), 0.0f, 1.0f },
			// (23) Bottom Bottom Right
			{ boxSize,-boxSize,-boxSize, D3DXVECTOR3( 0.0f, 1.0f, 0.0f), 1.0f, 1.0f }
		};
		
		// 3 indexes per triangle, 2 triangles per square, 6 squares per cube
		unsigned long indexArraySize	= ((3 * 2) * 6) * sizeof(short);
		short indices[]					=
		{
			// Front
			0, 1, 2,
			3, 2, 1,

			// Back
			5, 4, 7,
			6, 7, 4,

			// Left
			8, 9, 10,
			11, 10, 9,

			// Right
			12, 13, 14,
			15, 14, 13,

			// Top
			16, 17, 18,
			19, 18, 17,

			// Bottom
			20, 21, 22,
			23, 22, 21
		};

		// Create the vertex buffer
		argPRenderer->CreateVertexBuffer(&this->pVertexBuffer, vertexArraySize, D3DFVFTexturedVector3, vertices);

		// Create the index buffer
		argPRenderer->CreateIndexBuffer(&this->pIndexBuffer, indexArraySize, indices);
	}

	/**
	 * Nothing here yet...
	 * @return		void
	 */
	void Skybox::Update()
	{
	}

	/**
	 * Draws the skybox.
	 * @param		Renderer*			The renderer to use for drawing the skybox's vertices and texture.
	 * @return		void
	 */
	void Skybox::Draw(Renderer* argPRenderer)
	{
		// Reset the actual world matrix again.
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

		
		D3DXMatrixMultiply(&this->matWorld, (D3DXMATRIXA16*)argPRenderer->GetWorldTop(), &this->matWorld);

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

		argPRenderer->LoadWorldMatrix(&this->matWorld);

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

		// 3 vertices per corner
		unsigned long numVertices	= 8 * 3;
		// 2 triangles per square, 6 squares per cube
		unsigned long numPrimitives	= 6 * 2;
		argPRenderer->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, numVertices, numPrimitives);

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