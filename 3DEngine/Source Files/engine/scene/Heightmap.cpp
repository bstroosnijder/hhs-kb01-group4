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
		Logger::Log("Heightmap: Initializing", Logger::INFO, __FILE__, __LINE__);

		this->pBitmap = new Bitmap();

		for(unsigned long i = 0; i < 8; i++)
		{
			this->textures[i] = NULL;
		}

		this->numPrimitives = 0;
		this->numVertices = 0;
		
		Logger::Log("Heightmap: Finished", Logger::INFO, __FILE__, __LINE__);
	}
	
	/**
	 * Destructs the Heightmap object.
	 */
	Heightmap::~Heightmap()
	{
		Logger::Log("Heightmap: Disposing", Logger::INFO, __FILE__, __LINE__);
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

		if (imageWidth != imageHeight)
		{
			Logger::Log("Trying to load a non-sqaure bitmap. This may cause runtime errors", Logger::FATAL, __FILE__, __LINE__);
		}

		float offsetX					= -(((float)imageWidth) / 2);
		//float offsetX					= 0;
		float offsetY					= 0;
		float offsetZ					= -(((float)imageHeight) / 2);
		//float offsetZ					= 0;
		
		// --- Create the vertex array ---
		this->numPrimitives				= (imageWidth * imageHeight) * 2;
		this->numVertices				= imageWidth * imageHeight;
		unsigned long vertexArraySize	= this->numVertices * sizeof(TexturedVector3);

		TexturedVector3* vertices			= new TexturedVector3[this->numVertices];

		for(long z = 0; z < imageHeight; z++)
		{
			for(long x = 0; x < imageWidth; x++)
			{
				long vIndex				= (z * imageWidth) + x;
				float pixelX			= x * pixelDistance;
				float pixelY			= pixelData[vIndex] / 15.0f;
				float pixelZ			= z * pixelDistance;

				vertices[vIndex].x		= offsetX + pixelX;
				vertices[vIndex].y		= offsetY + pixelY;
				vertices[vIndex].z		= offsetZ + pixelZ;

				vertices[vIndex].u		= pixelX / ((float)imageWidth);
				vertices[vIndex].v		= 1 - (pixelZ / ((float)imageHeight));
			
			}
		}


		// Smooth the map
		this->SmoothMap(vertices, argSmoothing);
		
		// --- Create the index array ---
		unsigned long numIndices		= this->numPrimitives * 3;
		unsigned long indexArraySize	= numIndices * sizeof(short);

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
		argPRenderer->CreateIndexBuffer(&this->pIndexBuffer, indexArraySize, indices);
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

		// Load the textures
		for(unsigned long i = 0; i < 8; i++)
		{
			argPRenderer->SetTexture(i, this->textures[i]);
		}
		
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