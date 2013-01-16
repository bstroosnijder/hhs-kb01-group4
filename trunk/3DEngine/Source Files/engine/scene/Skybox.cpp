#include "..\..\..\Header Files\engine\scene\Skybox.h"

namespace engine
{
	/**
	 * Construct the Skybox object.
	 */
	Skybox::Skybox()
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
	void Skybox::SetupVertices(Renderer* argPRenderer, unsigned long argBoxSize)
	{
		float numFaces					= 6;
		float offset					= (argBoxSize - 1) / 2.0f;
		
		// --- Create the vertex array ---
		unsigned long numVerticesFace	= argBoxSize * argBoxSize;
		this->numVertices				= numVerticesFace * 6;
		this->numPrimitives				= this->numVertices * 2;
		unsigned long vertexArraySize	= this->numVertices * sizeof(TexturedVector3);
		TexturedVector3* vertices		= new TexturedVector3[this->numVertices];

		// For each side of the cube
		// (0) = Front
		// (1) = Back
		// (2) = Left
		// (3) = Right
		// (4) = Top
		// (5) = Bottom
		for(unsigned long iFace = 0; iFace < numFaces; iFace++)
		{
			unsigned long curIndex = iFace * numVerticesFace;
			for(long z = 0; z < argBoxSize; z++)
			{
				for(long x = 0; x < argBoxSize; x++)
				{
					unsigned long vIndex	= curIndex + ((z * argBoxSize) + x);

					float pixelX;
					float pixelY;
					float pixelZ;
					float pixelU;
					float pixelV;

					// Face: Front
					if(iFace == 0)
					{
						pixelX				= x - offset;
						pixelY				= offset - z;
						pixelZ				= offset;
						pixelU				= pixelX / argBoxSize;
						pixelV				= pixelY / argBoxSize;
					}
					// Face: Back
					else if(iFace == 1)
					{
						pixelX				= offset - x;
						pixelY				= offset - z;
						pixelZ				= -offset;
						pixelU				= pixelX / argBoxSize;
						pixelV				= pixelY / argBoxSize;
					}
					// Face: Left
					else if(iFace == 2)
					{
						pixelZ				= offset - x;
						pixelY				= offset - z;
						pixelX				= offset;
						pixelU				= pixelZ / argBoxSize;
						pixelV				= pixelY / argBoxSize;
					}
					// Face: Right
					else if(iFace == 3)
					{
						pixelZ				= x - offset;
						pixelY				= offset - z;
						pixelX				= -offset;
						pixelU				= pixelZ / argBoxSize;
						pixelV				= pixelY / argBoxSize;
					}
					// Face: Top
					else if(iFace == 4)
					{
						pixelX				= offset - x;
						pixelZ				= offset - z;
						pixelY				= offset;
						pixelU				= pixelX / argBoxSize;
						pixelV				= pixelZ / argBoxSize;
					}
					// Face: Bottom
					else
					{
						pixelX				= x - offset;
						pixelZ				= offset - z;
						pixelY				= -offset;
						pixelU				= pixelX / argBoxSize;
						pixelV				= pixelZ / argBoxSize;
					}

					vertices[vIndex].x		= pixelX;
					vertices[vIndex].y		= pixelY;
					vertices[vIndex].z		= pixelZ;
					vertices[vIndex].normal	= D3DXVECTOR3(-pixelX, -pixelY, -pixelZ);
					vertices[vIndex].u		= pixelU;
					vertices[vIndex].v		= pixelV;
				}
			}
		}


		// --- Create the index array ---
		unsigned long numIndices		= this->numPrimitives * 3;
		unsigned long indexArraySize	= numIndices * sizeof(short);
		short* indices					= new short[numIndices];
		
		int index						= 0;
		for(unsigned long iFace = 0; iFace < numFaces; iFace++)
		{
			unsigned long curIndex = iFace * numVerticesFace;
			for(long z = 0; z < (argBoxSize - 1); z++)
			{
				for(long x = 0; x < (argBoxSize - 1); x++)
				{
					// Top Left
					indices[index]			= (short)(curIndex + ((z * argBoxSize) + x));
					index++;
					// Top Right
					indices[index]			= (short)(curIndex + ((z * argBoxSize) + (x + 1)));
					index++;
					// Bottom Left
					indices[index]			= (short)(curIndex + (((z + 1) * argBoxSize) + x));
					index++;
				
					// Bottom Right
					indices[index]			= (short)(curIndex + (((z + 1) * argBoxSize) + (x + 1)));
					index++;
					// Bottom Left
					indices[index]			= (short)(curIndex + (((z + 1) * argBoxSize) + x));
					index++;
					// Top Right
					indices[index]			= (short)(curIndex + ((z * argBoxSize) + (x + 1)));
					index++;
				}
			}
		}

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
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);

		// Scaling
		D3DXMATRIXA16 matScaling;
		D3DXMatrixScaling(&matScaling, 1.0f, 1.0f, 1.0f);
		D3DXMatrixMultiply(&matWorld, &matWorld, &matScaling);

		// Rotation X
		D3DXMATRIXA16 matRotationX;
		D3DXMatrixRotationX(&matRotationX, 0.0f);
		D3DXMatrixMultiply(&matWorld, &matWorld, &matRotationX);
		// Rotation Y
		D3DXMATRIXA16 matRotationY;
		D3DXMatrixRotationY(&matRotationY, 0.0f);
		D3DXMatrixMultiply(&matWorld, &matWorld, &matRotationY);
		// Rotation Z
		D3DXMATRIXA16 matRotationZ;
		D3DXMatrixRotationZ(&matRotationZ, 0.0f);
		D3DXMatrixMultiply(&matWorld, &matWorld, &matRotationZ);

		
		D3DXMatrixMultiply(&matWorld, (D3DXMATRIXA16*)argPRenderer->GetWorldTop(), &matWorld);

		D3DXVECTOR3 vecScale;
		D3DXQUATERNION quatRotation;
		D3DXVECTOR3 vecTranslation;
		// Decompose the current world matrix, we need this so we counter camera movement and keep the skybox still
		D3DXMatrixDecompose(&vecScale, &quatRotation, &vecTranslation, &matWorld);
		
		// Position
		D3DXMATRIXA16 matTranslation;
		D3DXMatrixTranslation(&matTranslation, vecTranslation.x, vecTranslation.y, vecTranslation.z);
		D3DXMatrixInverse(&matTranslation, NULL, &matTranslation);
		D3DXMatrixMultiply(&matWorld, &matWorld, &matTranslation);

		argPRenderer->LoadWorldMatrix(&matWorld);

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
		argPRenderer->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, this->numVertices, this->numPrimitives);

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