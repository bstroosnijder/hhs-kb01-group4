#ifndef HEIGHTMAP_H_
#define HEIGHTMAP_H_

#include <d3dx9.h>
#include "..\logger\Logger.h"
#include "Drawable.h"
#include "..\utils\Bitmap.h"
#include "..\utils\TexturedVector3.h"
#include "..\renderer\Renderer.h"

namespace engine
{
	/**
	 * Uses an 8bit BMP file to generate a heigtmap terrain
	 */
	class Heightmap : public Drawable
	{
	private:
		long width;
		long height;
		float offsetX;
		float offsetY;
		float offsetZ;
		
		unsigned long numVertices;
		unsigned long numPrimitives;
		TexturedVector3* vertices;

		LPDIRECT3DTEXTURE9 textures[8];

		LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
		LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
		
		void SmoothMap(unsigned long argNumIterations);
		void CalculateNormals();
	public:
		Heightmap();
		~Heightmap();
		void CleanUp();
		
		void SetupVertices(Renderer* argPRenderer, std::string argMapFileName, float argPixelScale, unsigned long argSmoothing);
		float GetHeight(float argX, float argZ);

		void Update();
		void Draw(Renderer* argPRenderer);

		void SetTexture(unsigned long argIndex, LPDIRECT3DTEXTURE9 argTexture);
	};
}

#endif