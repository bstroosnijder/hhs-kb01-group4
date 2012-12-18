#ifndef HEIGHTMAP_H_
#define HEIGHTMAP_H_

#include "..\..\..\Header Files\engine\renderer\DirectX9Renderer.h"

struct CUSTOMVERTEX
{
    FLOAT x, y, z;      // The untransformed, 3D position for the vertex
    DWORD color;        // The vertex color
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

namespace engine
{
	class Heightmap
	{
	private:
		LPDIRECT3DVERTEXBUFFER9 g_pVB;
	public:
		void Init(Renderer* argPRenderer);
		void Draw(Renderer* argPRenderer);
	};
}

#endif