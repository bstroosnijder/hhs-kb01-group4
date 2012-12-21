#include "..\..\..\Header Files\engine\scene\Heightmap.h"

namespace engine
{
	void Heightmap::SmoothMap(CUSTOMVERTEX* argVertices, unsigned long argNumIterations)
	{
		// check if the iteration count has reached 0
		if(argNumIterations == 0)
		{
			return;
		}
		unsigned long numIterationsLeft	= argNumIterations - 1;

		long imageWidth					= this->pBitmap->GetImageWidth();
		long imageHeight				= this->pBitmap->GetImageHeight();

		CUSTOMVERTEX* newVertices		= new CUSTOMVERTEX[this->numVertices];
		
		// Calculate new Y value, but don't set it yet or we corrupt the data
		for(long z = 0; z < imageHeight; z++)
		{
			for(long x = 0; x < imageWidth; x++)
			{
				long vIndex	= (z * imageWidth) + x;

				int numSections			= 0;
				float sectionsTotal		= 0.0f;

				// Check: left
				if((x - 1) >= 0)
				{
					numSections++;
					sectionsTotal += argVertices[vIndex - 1].y;

					// Check: left top
					if((z - 1) >= 0)
					{
						numSections++;
						sectionsTotal += argVertices[(vIndex - 1) - imageWidth].y;
					}

					// Check: left bottom
					if((z + 1) < imageHeight)
					{
						numSections++;
						sectionsTotal += argVertices[(vIndex - 1) + imageWidth].y;
					}
				}

				// Check: right
				if((x + 1) < imageWidth)
				{
					numSections++;
					sectionsTotal += argVertices[vIndex + 1].y;

					// Check: right top
					if((z - 1) >= 0)
					{
						numSections++;
						sectionsTotal += argVertices[(vIndex + 1) - imageWidth].y;
					}

					// Check: right bottom
					if((z + 1) < imageHeight)
					{
						numSections++;
						sectionsTotal += argVertices[(vIndex + 1) + imageWidth].y;
					}
				}

				// Check: top
				if((z - 1) >= 0)
				{
					numSections++;
					sectionsTotal += argVertices[vIndex - imageWidth].y;
				}

				// Check: bottom
				if((z + 1) < imageHeight)
				{
					numSections++;
					sectionsTotal += argVertices[vIndex + imageWidth].y;
				}

				// Set the new value
				newVertices[vIndex].y = (argVertices[vIndex].y + (sectionsTotal / numSections)) * 0.5f;
			}
		}

		// Actually set the new values
		for(long z = 0; z < imageHeight; z++)
		{
			for(long x = 0; x < imageWidth; x++)
			{
				long vIndex	= (z * imageWidth) + x;
				argVertices[vIndex].y	= newVertices[vIndex].y;
			}
		}


		// Rerun the algorithm
		this->SmoothMap(argVertices, numIterationsLeft);
	}

	Heightmap::Heightmap()
	{
		this->pBitmap = new Bitmap();

		this->numPrimitives = 0;
		this->numVertices = 0;
	}

	Heightmap::~Heightmap()
	{
		this->CleanUp();
	}

	void Heightmap::CleanUp()
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

	void Heightmap::LoadMap(std::string argMapFileName)
	{
		this->pBitmap->Load(argMapFileName);
	}

	void Heightmap::SetupVertices(Renderer* argPRenderer, unsigned long argSmoothing)
	{
		DirectX9Renderer* pRenderer		= (DirectX9Renderer*)argPRenderer;
		
		float pixelDistance				= 1;
		unsigned long pixelColor1		= 0xFFFF0000;
		unsigned long pixelColor2		= 0xFF0000FF;
		unsigned char* pixelData		= this->pBitmap->GetPixelData();
		long imageWidth					= this->pBitmap->GetImageWidth();
		long imageHeight				= this->pBitmap->GetImageHeight();

		float offsetX					= -(((float)imageWidth) / 2);
		float offsetY					= 0;
		float offsetZ					= -(((float)imageHeight) / 2);
		
		// --- Create the vertex array ---
		this->numPrimitives				= (imageWidth * imageHeight) * 2;
		this->numVertices				= imageWidth * imageHeight;
		unsigned long vertexArraySize	= this->numVertices * sizeof(CUSTOMVERTEX);

		CUSTOMVERTEX* vertices			= new CUSTOMVERTEX[this->numVertices];

		for(long z = 0; z < imageHeight; z++)
		{
			for(long x = 0; x < imageWidth; x++)
			{
				long vIndex	= (z * imageWidth) + x;
				float pixelX			= offsetX + (x * pixelDistance);
				float pixelY			= offsetY + pixelData[vIndex] / 15.0f;
				float pixelZ			= offsetZ + (z * pixelDistance);

				vertices[vIndex].x		= pixelX;
				vertices[vIndex].y		= pixelY;
				vertices[vIndex].z		= pixelZ;

				if(pixelY >= 0.5f)
				{
					vertices[vIndex].color	= pixelColor1;
				}
				else
				{
					vertices[vIndex].color	= pixelColor2;
				}

				if(vIndex % 2 == 0)
				{
					// TODO: figure out how to make this dynamic
					// it has to do with how the texture is multiplied over the primitives
					// with the current numbers it puts 1 image on 1 primitive
					vertices[vIndex].u		= ((float)vIndex) / (128 - 1);
					vertices[vIndex].v		= 1.0f;
				}
				else
				{
					vertices[vIndex].u		= ((float)vIndex) / (128 - 1);
					vertices[vIndex].v		= 0.0f;
				}
			}
		}

		// Smooth the map
		this->SmoothMap(vertices, argSmoothing);
		
		// --- Create the index array ---
		unsigned long numIndices		= this->numPrimitives * 3;
		unsigned long indiceArraySize	= numIndices * sizeof(short);

		short* indices					= new short[numIndices];
		
		int index						= 0;
		for(long z = 0; z < (imageHeight - 1); z++)
		{
			for(long x = 0; x < (imageWidth - 1); x++)
			{
				// Top Left
				indices[index]			= (short)((z * imageWidth) + x);
				index++;
				// Bottom Left
				indices[index]			= (short)(((z + 1) * imageWidth) + x);
				index++;
				// Top Right
				indices[index]			= (short)((z * imageWidth) + (x + 1));
				index++;
				
				// Bottom Right
				indices[index]			= (short)(((z + 1) * imageWidth) + (x + 1));
				index++;
				// Top Right
				indices[index]			= (short)((z * imageWidth) + (x + 1));
				index++;
				// Bottom Left
				indices[index]			= (short)(((z + 1) * imageWidth) + x);
				index++;
			}
		}


		// Create the vertex buffer.
		pRenderer->GetDevice()->CreateVertexBuffer(	vertexArraySize,
													0, D3DFVF_CUSTOMVERTEX,
													D3DPOOL_DEFAULT, &this->pVertexBuffer, NULL );

		// Create the index buffer.
		pRenderer->GetDevice()->CreateIndexBuffer(	indiceArraySize,
													0, D3DFMT_INDEX16,
													D3DPOOL_DEFAULT, &this->pIndexBuffer, NULL);

		void* pVertices;
		// Fill the vertex buffer.
		this->pVertexBuffer->Lock(0, vertexArraySize, (void**)&pVertices, 0);
		memcpy(pVertices, vertices, vertexArraySize);
		this->pVertexBuffer->Unlock();
		// Remove the vertex array
		delete vertices;
		
		void* pIndices;
		// Fill the index buffer.
		this->pIndexBuffer->Lock(0, indiceArraySize, (void**)&pIndices, 0);
		memcpy(pIndices, indices, indiceArraySize);
		this->pIndexBuffer->Unlock();
		// Remove the indice array
		delete indices;
	}

	void Heightmap::Draw(Renderer* argPRenderer)
	{
		DirectX9Renderer* pRenderer = (DirectX9Renderer*)argPRenderer;

		pRenderer->TransformWorldMatrix();
		pRenderer->TransformViewMatrix();
		pRenderer->TransformProjectionMatrix();
		
		pRenderer->GetDevice()->SetStreamSource(0, this->pVertexBuffer, 0, sizeof(CUSTOMVERTEX));
		pRenderer->GetDevice()->SetFVF(D3DFVF_CUSTOMVERTEX);
		pRenderer->GetDevice()->SetIndices(this->pIndexBuffer);

		pRenderer->GetDevice()->SetTexture(0, this->textures[0]);
        pRenderer->GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        pRenderer->GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        pRenderer->GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
        pRenderer->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

		pRenderer->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, this->numVertices, 0, this->numPrimitives);
	}
	
	void Heightmap::SetTexture(unsigned long argIndex, LPDIRECT3DTEXTURE9 argTexture)
	{
		this->textures[argIndex] = argTexture;
	}
}