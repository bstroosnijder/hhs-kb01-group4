#ifndef HEIGHTMAP_H_
#define HEIGHTMAP_H_

#include <d3dx9.h>
#include "..\logger\Logger.h"
#include "Drawable.h"
#include "..\utils\Bitmap.h"
#include "..\utils\TexturedVector3.h"
#include "..\renderer\Renderer.h"

// Our custom FVF, which describes our custom vertex structure
#define D3DFVFTexturedVector3 (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

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

		unsigned long numPrimitives;
		unsigned long numVertices;

		LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
		LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
		
		void SmoothMap(TexturedVector3* argVertices, unsigned long argNumIterations);
	public:
		Heightmap();
		~Heightmap();
		void CleanUp();
		
		void LoadMap(std::string argMapFileName);
		void SetupVertices(Renderer* argPRenderer, unsigned long argSmoothing);

		void Update();
		void Draw(Renderer* argPRenderer);

		void SetTexture(unsigned long argIndex, LPDIRECT3DTEXTURE9 argTexture);
	};
}

#endif