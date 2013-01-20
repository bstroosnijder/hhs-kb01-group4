#include "..\..\..\Header Files\engine\scene\Skybox.h"

namespace engine
{
	/**
	 * Construct the Skybox object.
	 */
	Skybox::Skybox()
	{
		Logger::Log("Skybox: Initializing", Logger::INFO, __FILE__, __LINE__);

		this->position = Vector3(0.0f, 0.0f, 0.0f);

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
	 * Getter for the size
	 * @return		float
	 */
	float Skybox::GetSize()
	{
		return this->size;
	}
	
	/**
	 * Setter for the position
	 * @param		Vector3					The new position for the skybox
	 * @return		void
	 */
	void Skybox::SetPosition(Vector3 argPosition)
	{
		this->position = argPosition;
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
		this->size						= argBoxSize;
		float offset					= (this->size - 1) / 2.0f;
		
		// --- Create the vertex array ---
		unsigned long numVerticesFace	= this->size * this->size;
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
			for(unsigned long z = 0; z < this->size; z++)
			{
				for(unsigned long x = 0; x < this->size; x++)
				{
					unsigned long vIndex	= curIndex + ((z * this->size) + x);

					float pixelX;
					float pixelY;
					float pixelZ;

					// Face: Front
					if(iFace == 0)
					{
						pixelX				= x - offset;
						pixelY				= offset - z;
						pixelZ				= offset;
					}
					// Face: Back
					else if(iFace == 1)
					{
						pixelX				= offset - x;
						pixelY				= offset - z;
						pixelZ				= -offset;
					}
					// Face: Left
					else if(iFace == 2)
					{
						pixelZ				= offset - x;
						pixelY				= offset - z;
						pixelX				= offset;
					}
					// Face: Right
					else if(iFace == 3)
					{
						pixelZ				= x - offset;
						pixelY				= offset - z;
						pixelX				= -offset;
					}
					// Face: Top
					else if(iFace == 4)
					{
						pixelX				= offset - x;
						pixelZ				= offset - z;
						pixelY				= offset;
					}
					// Face: Bottom
					else
					{
						pixelX				= x - offset;
						pixelZ				= offset - z;
						pixelY				= -offset;
					}

					vertices[vIndex].x		= pixelX;
					vertices[vIndex].y		= pixelY;
					vertices[vIndex].z		= pixelZ;
					vertices[vIndex].normal	= D3DXVECTOR3(-pixelX, -pixelY, -pixelZ);
					vertices[vIndex].u		= (float)x / (float)(this->size - 1);
					vertices[vIndex].v		= (float)z / (float)(this->size - 1);
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
			for(unsigned long z = 0; z < (this->size - 1); z++)
			{
				for(unsigned long x = 0; x < (this->size - 1); x++)
				{
					// Top Left
					indices[index]			= (short)(curIndex + ((z * this->size) + x));
					index++;
					// Top Right
					indices[index]			= (short)(curIndex + ((z * this->size) + (x + 1)));
					index++;
					// Bottom Left
					indices[index]			= (short)(curIndex + (((z + 1) * this->size) + x));
					index++;
				
					// Bottom Right
					indices[index]			= (short)(curIndex + (((z + 1) * this->size) + (x + 1)));
					index++;
					// Bottom Left
					indices[index]			= (short)(curIndex + (((z + 1) * this->size) + x));
					index++;
					// Top Right
					indices[index]			= (short)(curIndex + ((z * this->size) + (x + 1)));
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

		// Rotation
		D3DXMATRIXA16 matRotation;
		D3DXMatrixRotationYawPitchRoll(&matRotation, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&matWorld, &matWorld, &matRotation);

		// Position
		D3DXMATRIXA16 matPosition;
		D3DXMatrixTranslation(&matPosition, this->position.x, this->position.y, this->position.z);
		D3DXMatrixMultiply(&matWorld, &matWorld, &matPosition);

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