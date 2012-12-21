#ifndef HEIGHTMAP_H_
#define HEIGHTMAP_H_

#include <d3dx9.h>
#include "..\utils\Vector3.h"
#include "..\utils\Bitmap.h"
#include "..\renderer\DirectX9Renderer.h"

struct CUSTOMVERTEX
{
	float x;
	float y;
	float z;
    unsigned long color;
	//CUSTOMVERTEX(){}
	//CUSTOMVERTEX(float x, float y, float z, unsigned long color) : x(x),y(y),z(z),color(color) {}
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

namespace engine
{
	class Heightmap
	{
	private:
		Bitmap* pBitmap;
		LPDIRECT3DTEXTURE9 textures[8];

		unsigned long numPrimitives;
		unsigned long numVertices;

		LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
		LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
	public:
		Heightmap();
		~Heightmap();
		void CleanUp();
		
		void LoadMap(std::string argMapFileName);
		void SetupVertices(Renderer* argPRenderer);
		void Draw(Renderer* argPRenderer);

		void SetTexture(unsigned long argIndex, LPDIRECT3DTEXTURE9 argTexture);
	};
}

#endif