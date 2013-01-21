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
	 * @param		unsigned long			The number of iterations to execute this function
	 * @return		void
	 */
	void Heightmap::SmoothMap(unsigned long argNumIterations)
	{
		// check if the iteration count has reached 0
		if(argNumIterations == 0)
		{
			return;
		}
		unsigned long numIterationsLeft	= argNumIterations - 1;

		TexturedVector3* tempVertices	= new TexturedVector3[this->numVertices];
		// Calculate new Y value, but don't set it yet or we corrupt the data
		for(long z = 0; z < this->height; z++)
		{
			for(long x = 0; x < this->width; x++)
			{
				long vIndex	= (z * this->width) + x;

				int numSections			= 0;
				float sectionsTotal		= 0.0f;

				// Check: left
				if((x - 1) >= 0)
				{
					numSections++;
					sectionsTotal += this->vertices[vIndex - 1].y;

					// Check: left top
					if((z - 1) >= 0)
					{
						numSections++;
						sectionsTotal += this->vertices[(vIndex - 1) - this->width].y;
					}

					// Check: left bottom
					if((z + 1) < this->height)
					{
						numSections++;
						sectionsTotal += this->vertices[(vIndex - 1) + this->width].y;
					}
				}

				// Check: right
				if((x + 1) < this->width)
				{
					numSections++;
					sectionsTotal += this->vertices[vIndex + 1].y;

					// Check: right top
					if((z - 1) >= 0)
					{
						numSections++;
						sectionsTotal += this->vertices[(vIndex + 1) - this->width].y;
					}

					// Check: right bottom
					if((z + 1) < this->height)
					{
						numSections++;
						sectionsTotal += this->vertices[(vIndex + 1) + this->width].y;
					}
				}

				// Check: top
				if((z - 1) >= 0)
				{
					numSections++;
					sectionsTotal += this->vertices[vIndex - this->width].y;
				}

				// Check: bottom
				if((z + 1) < this->height)
				{
					numSections++;
					sectionsTotal += this->vertices[vIndex + this->width].y;
				}

				// Set the new value
				tempVertices[vIndex].y = (this->vertices[vIndex].y + (sectionsTotal / numSections)) * 0.5f;
			}
		}

		// Actually set the new values
		for(long z = 0; z < this->height; z++)
		{
			for(long x = 0; x < this->width; x++)
			{
				long vIndex	= (z * this->width) + x;
				this->vertices[vIndex].y	= tempVertices[vIndex].y;
			}
		}

		// Clean up the temp vertices
		delete tempVertices;

		// Rerun the algorithm
		this->SmoothMap(numIterationsLeft);
	}

	/**
	 * Calculates the normals of the heightmap
	 * @return		void
	 */
	void Heightmap::CalculateNormals()
	{
		for(long z = 0; z < this->height; z++)
		{
			for(long x = 0; x < this->width; x++)
			{
				long vIndex	= (z * this->width) + x;

				float normalX	= 0.0f;
				float normalY	= 1.0f;
				float normalZ	= 0.0f;

				if(x > 0)
				{
					normalX		+= this->vertices[vIndex - 1].y;
				}

				if(x < (this->width - 1))
				{
					normalX		-= this->vertices[vIndex + 1].y;
				}

				if(z > 0)
				{
					normalZ		+= this->vertices[vIndex - this->width].y;
				}

				if(z < (this->height - 1))
				{
					normalZ		-= this->vertices[vIndex + this->width].y;
				}

				
				this->vertices[vIndex].normal.x	= normalX;
				this->vertices[vIndex].normal.y	= normalY;
				this->vertices[vIndex].normal.z	= normalZ;
			}
		}
	}
	
	//---Public methods---
	
	/**
	 * Constructs the Heightmap object.
	 */
	Heightmap::Heightmap()
	{
		Logger::Log("Heightmap: Initializing", Logger::INFO, __FILE__, __LINE__);

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
	 * Gets the scaling
	 * @return		float
	 */
	float Heightmap::GetScaling()
	{
		return this->scaling;
	}

	/**
	 * Gets the smoothing
	 * @return		long
	 */
	long Heightmap::GetSmoothing()
	{
		return this->smoothing;
	}

	/**
	 * Takes the pixel data from the Bitmap class and generates a vertices array with the Y value as the pixel value.
	 * @param		Renderer*				The renderer to use
	 * @param		std::string				The file name of the BMP file to load
	 * @param		float					The scaling of each pixel
	 * @param		unsigned long			The number of smoothing iteration to do
	 * @return		void
	 */
	void Heightmap::SetupVertices(Renderer* argPRenderer, std::string argMapFileName, float argPixelScale, unsigned long argSmoothing)
	{
		// Load the bitmap
		Bitmap* pBitmap					= new Bitmap();
		pBitmap->Load(argMapFileName);

		// Fetch the bitmap data, width and height
		unsigned char* pixelData		= pBitmap->GetPixelData();
		this->width						= pBitmap->GetImageWidth();
		this->height					= pBitmap->GetImageHeight();
		
		// Save the heightmap data
		this->scaling					= argPixelScale;
		this->smoothing					= argSmoothing;

		// Delete the bitmap
		delete pBitmap;

		this->offsetX					= -(((float)(this->width * this->scaling)) / 2);
		this->offsetY					= 0;
		this->offsetZ					= -(((float)(this->height * this->scaling)) / 2);
		
		// --- Create the vertex array ---
		this->numVertices				= this->width * this->height;
		this->numPrimitives				= this->numVertices * 2;
		unsigned long vertexArraySize	= this->numVertices * sizeof(TexturedVector3);
		this->vertices					= new TexturedVector3[this->numVertices];

		for(long z = 0; z < this->height; z++)
		{
			for(long x = 0; x < this->width; x++)
			{
				long vIndex						= (z * this->width) + x;
				float pixelX					= x * this->scaling;
				float pixelY					= pixelData[vIndex] / 15.0f;
				float pixelZ					= z * this->scaling;

				this->vertices[vIndex].x		= this->offsetX + pixelX;
				this->vertices[vIndex].y		= this->offsetY + pixelY;
				this->vertices[vIndex].z		= this->offsetZ + pixelZ;

				this->vertices[vIndex].normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				this->vertices[vIndex].u		= pixelX / ((float)(this->width * this->scaling));
				this->vertices[vIndex].v		= 1 - (pixelZ / ((float)(this->height * this->scaling)));
			}
		}


		// Smooth the map
		this->SmoothMap(argSmoothing);
		// Calculate the normals
		this->CalculateNormals();

		
		// --- Create the index array ---
		unsigned long numIndices		= this->numPrimitives * 3;
		unsigned long indexArraySize	= numIndices * sizeof(short);

		short* indices					= new short[numIndices];
		
		int index						= 0;
		for(long z = 0; z < (this->height - 1); z++)
		{
			for(long x = 0; x < (this->width - 1); x++)
			{
				// Top Left
				indices[index]			= (short)((z * this->width) + x);
				index++;
				// Bottom Left
				indices[index]			= (short)(((z + 1) * this->width) + x);
				index++;
				// Top Right
				indices[index]			= (short)((z * this->width) + (x + 1));
				index++;
				
				// Bottom Right
				indices[index]			= (short)(((z + 1) * this->width) + (x + 1));
				index++;
				// Top Right
				indices[index]			= (short)((z * this->width) + (x + 1));
				index++;
				// Bottom Left
				indices[index]			= (short)(((z + 1) * this->width) + x);
				index++;
			}
		}

		
		// Create the vertex buffer.
		argPRenderer->CreateVertexBuffer(&this->pVertexBuffer, vertexArraySize, D3DFVFTexturedVector3, this->vertices);
		
		// Create the index buffer.
		argPRenderer->CreateIndexBuffer(&this->pIndexBuffer, indexArraySize, indices);
	}
	
	/**
	 * Get the height data from an X and Z coordinate
	 * @param		long		The x coordinate
	 * @param		long		The Z coordinate
	 * @return		float		The Y value (height data)
	 */
	float Heightmap::GetHeight(float argX, float argZ)
	{
		int num		= 0;
		float sum	= 0.0f;

		long ceilX	= (long)std::ceil(argX - this->offsetX);
		long ceilZ	= (long)std::ceil(argZ - this->offsetZ);
		long floorX	= (long)std::floor(argX - this->offsetX);
		long floorZ	= (long)std::floor(argZ - this->offsetZ);

		// Top
		if(ceilZ < ((this->offsetZ + this->height) - 1))
		{
			// Left
			if(floorX > this->offsetX)
			{
				num++;
				sum+= this->vertices[(ceilZ * this->width) + floorX].y;
			}

			// Right
			if(ceilX < ((this->offsetZ + this->width) - 1))
			{
				num++;
				sum+= this->vertices[(ceilZ * this->width) + ceilX].y;
			}
		}

		// Bottom
		if(floorZ > this->offsetZ)
		{
			// Left
			if(floorX > this->offsetX)
			{
				num++;
				sum+= this->vertices[(floorZ * this->width) + floorX].y;
			}

			// Right
			if(ceilX < ((this->offsetZ + this->width) - 1))
			{
				num++;
				sum+= this->vertices[(floorZ * this->width) + ceilX].y;
			}
		}

		// Return the average height of the 4 pixels
		return sum / num;
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