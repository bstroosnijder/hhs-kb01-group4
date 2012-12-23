#include "..\..\..\Header Files\engine\scene\Heightmap.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---

	/**
	 * Will check every position in the vetices array it's giving and tries to smooth out the values.
	 * The smoothing works by taking the sum of the 8 surrounding vertices.
	 * Adding it's own value to that and deviding it by 2. This gives us the average of the 2 values 
	 * and makes the terrain smoother.
	 * 
	 * @param		TexturedVector3*		The array with vertices to smooth out
	 * @param		unsigned long			The number of iterations to execute this function
	 * @return		void
	 */
	void Heightmap::SmoothMap(TexturedVector3* argVertices, unsigned long argNumIterations)
	{
		// check if the iteration count has reached 0
		if(argNumIterations == 0)
		{
			return;
		}
		unsigned long numIterationsLeft	= argNumIterations - 1;

		long imageWidth					= this->pBitmap->GetImageWidth();
		long imageHeight				= this->pBitmap->GetImageHeight();

		TexturedVector3* tempVertices	= new TexturedVector3[this->numVertices];
		
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
				tempVertices[vIndex].y = (argVertices[vIndex].y + (sectionsTotal / numSections)) * 0.5f;
			}
		}

		// Actually set the new values
		for(long z = 0; z < imageHeight; z++)
		{
			for(long x = 0; x < imageWidth; x++)
			{
				long vIndex	= (z * imageWidth) + x;
				argVertices[vIndex].y	= tempVertices[vIndex].y;
			}
		}

		// Clean up the temp vertices
		delete tempVertices;

		// Rerun the algorithm
		this->SmoothMap(argVertices, numIterationsLeft);
	}
	
	//---Public methods---
	
	/**
	 * Constructs the Heightmap object.
	 */
	Heightmap::Heightmap()
	{
		this->pBitmap = new Bitmap();

		this->numPrimitives = 0;
		this->numVertices = 0;
	}
	
	/**
	 * Destructs the Heightmap object.
	 */
	Heightmap::~Heightmap()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
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

	/**
	 * Passes the file forward to the bitmap class so that it can load the pixel data.
	 * @param		std::string				The file name of the BMP file to load
	 */
	void Heightmap::LoadMap(std::string argMapFileName)
	{
		this->pBitmap->Load(argMapFileName);
	}

	/**
	 * Takes the pixel data from the Bitmap class and generates a vertices array with the Y value as the pixel value.
	 * @param		Renderer*				The renderer to use
	 * @param		unsigned long			The number of smoothing iteration to do
	 * @return		void
	 */
	void Heightmap::SetupVertices(Renderer* argPRenderer, unsigned long argSmoothing)
	{
		float pixelDistance				= 1;
		unsigned char* pixelData		= this->pBitmap->GetPixelData();
		long imageWidth					= this->pBitmap->GetImageWidth();
		long imageHeight				= this->pBitmap->GetImageHeight();

		float offsetX					= -(((float)imageWidth) / 2);
		float offsetY					= 0;
		float offsetZ					= -(((float)imageHeight) / 2);
		
		// --- Create the vertex array ---
		this->numPrimitives				= (imageWidth * imageHeight) * 2;
		this->numVertices				= imageWidth * imageHeight;
		unsigned long vertexArraySize	= this->numVertices * sizeof(TexturedVector3);

		TexturedVector3* vertices			= new TexturedVector3[this->numVertices];

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

				if(pixelY >= 12.0f)
				{
					vertices[vIndex].color	= 0xFFFF0000;
				}
				else if(pixelY < 0.3f)
				{
					vertices[vIndex].color	= 0xFF0000FF;
				}
				else
				{
					vertices[vIndex].color	= 0xFFcccccc * ((unsigned long)pixelY);
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
		argPRenderer->CreateVertexBuffer(&this->pVertexBuffer, vertexArraySize, D3DFVFTexturedVector3, vertices);
		delete vertices;
		
		// Create the index buffer.
		argPRenderer->CreateIndexBuffer(&this->pIndexBuffer, indiceArraySize, indices);
		delete indices;
	}

	/**
	 * The update method
	 * @return		void
	 */
	void Heightmap::Update()
	{
	}

	/**
	 * Renders the terrain
	 * @param		Renderer*				The renderer to use
	 * @return		void
	 */
	void Heightmap::Draw(Renderer* argPRenderer)
	{
		argPRenderer->TransformWorldMatrix();
		argPRenderer->TransformViewMatrix();
		argPRenderer->TransformProjectionMatrix();
		
		argPRenderer->SetStreamSource(this->pVertexBuffer, sizeof(TexturedVector3));
		argPRenderer->SetFVF(D3DFVFTexturedVector3);
		argPRenderer->SetIndices(this->pIndexBuffer);

		argPRenderer->SetTexture(0, this->textures[0]);

		argPRenderer->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, this->numVertices, this->numPrimitives);
	}
	
	/**
	 * Sets a texture at a given index
	 * @param		unsigned long			The index to place the texture at
	 * @param		LPDIRECT3DTEXTURE9		The texture to draw on the giving index
	 * @return		void
	 */
	void Heightmap::SetTexture(unsigned long argIndex, LPDIRECT3DTEXTURE9 argTexture)
	{
		this->textures[argIndex] = argTexture;
	}
}