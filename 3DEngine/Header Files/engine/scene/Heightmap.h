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
		Bitmap* pBitmap;
		LPDIRECT3DTEXTURE9 textures[8];
		
		unsigned long numVertices;
		unsigned long numPrimitives;

		LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
		LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
		
		void SmoothMap(TexturedVector3* argVertices, unsigned long argNumIterations);
		void CalculateNormals(TexturedVector3* argVertices);
	public:
		Heightmap();
		~Heightmap();
		void CleanUp();
		
		void LoadMap(std::string argMapFileName);
		void SetupVertices(Renderer* argPRenderer, float argPixelScale, unsigned long argSmoothing);

		void Update();
		void Draw(Renderer* argPRenderer);

		void SetTexture(unsigned long argIndex, LPDIRECT3DTEXTURE9 argTexture);
	};
}

#endif