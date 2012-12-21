#include "..\..\..\Header Files\engine\scene\Heightmap.h"

namespace engine
{
	Heightmap::Heightmap()
	{
		this->pBitmap = new Bitmap();

		this->numPrimitives = 0;
		this->numVertices = 0;
	}

	Heightmap::~Heightmap()
	{
	}

	void Heightmap::CleanUp()
	{
	}

	void Heightmap::LoadMap(std::string argMapFileName)
	{
		this->pBitmap->Load(argMapFileName);
	}

	void Heightmap::SetupVertices(Renderer* argPRenderer)
	{
		DirectX9Renderer* pRenderer		= (DirectX9Renderer*)argPRenderer;
		
		float pixelDistance				= 1;
		unsigned long pixelColor		= 0xFF00FF00;
		unsigned char* pixelData		= this->pBitmap->GetPixelData();
		unsigned long imageWidth		= this->pBitmap->GetImageWidth();
		unsigned long imageHeight		= this->pBitmap->GetImageHeight();

		float offsetX					= 0;
		float offsetY					= 0;
		float offsetZ					= 0;
		
		// --- Create the vertex array ---
		this->numPrimitives				= (imageWidth * imageHeight) * 2;
		this->numVertices				= imageWidth * imageHeight;
		unsigned long vertexArraySize	= this->numVertices * sizeof(CUSTOMVERTEX);

		CUSTOMVERTEX* vertices			= new CUSTOMVERTEX[this->numVertices];

		for(unsigned long z = 0; z < imageHeight; z++)
		{
			for(unsigned long x = 0; x < imageWidth; x++)
			{
				unsigned long vIndex	= (z * imageWidth) + x;
				float pixelX			= offsetX + (x * pixelDistance);
				float pixelY			= offsetY + pixelData[vIndex] / 50;
				float pixelZ			= offsetZ + (z * pixelDistance);

				vertices[vIndex].x		= pixelX;
				vertices[vIndex].y		= pixelY;
				vertices[vIndex].z		= pixelZ;
				vertices[vIndex].color	= pixelColor;
			}
		}
		
		// --- Create the index array ---
		unsigned long numIndices		= this->numPrimitives * 3;
		unsigned long indiceArraySize	= numIndices * sizeof(short);

		short* indices					= new short[numIndices];
		
		unsigned long index				= 0;
		for(unsigned long z = 0; z < (imageHeight - 1); z++)
		{
			for(unsigned long x = 0; x < (imageWidth - 1); x++)
			{
				CUSTOMVERTEX vertex;
				// Top Left
				indices[index]			= (z * imageWidth) + x;
				index++;
				// Bottom Left
				indices[index]			= ((z + 1) * imageWidth) + x;
				index++;
				// Top Right
				indices[index]			= (z * imageWidth) + (x + 1);
				index++;
				
				// Bottom Right
				indices[index]			= ((z + 1) * imageWidth) + (x + 1);
				index++;
				// Top Right
				indices[index]			= (z * imageWidth) + (x + 1);
				index++;
				// Bottom Left
				indices[index]			= ((z + 1) * imageWidth) + x;
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

		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		pRenderer->AddToWorldMatrix(&matWorld);

		pRenderer->TransformWorldMatrix();
		pRenderer->TransformViewMatrix();
		pRenderer->TransformProjectionMatrix();

		pRenderer->GetDevice()->SetStreamSource(0, this->pVertexBuffer, 0, sizeof(CUSTOMVERTEX));
		pRenderer->GetDevice()->SetFVF(D3DFVF_CUSTOMVERTEX);
		pRenderer->GetDevice()->SetIndices(this->pIndexBuffer);
		pRenderer->GetDevice()->SetTexture(0, this->textures[0]);
		pRenderer->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, this->numVertices, 0, this->numPrimitives);
	}
	
	void Heightmap::SetTexture(unsigned long argIndex, LPDIRECT3DTEXTURE9 argTexture)
	{
		this->textures[argIndex] = argTexture;
	}
}