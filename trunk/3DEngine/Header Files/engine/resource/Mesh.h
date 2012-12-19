#ifndef MESH_H_
#define MESH_H_

#include <d3dx9.h>

namespace engine
{
	struct Mesh
	{
		LPD3DXMESH mesh;
		D3DMATERIAL9* materials;
		LPDIRECT3DTEXTURE9* textures;
		unsigned long numMaterials;
	};
}

#endif