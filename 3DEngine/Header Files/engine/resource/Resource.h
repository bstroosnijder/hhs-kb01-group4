#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <d3dx9.h>
#include "Mesh.h"

namespace engine
{
	struct Resource
	{
		Mesh* pMesh;
		LPDIRECT3DTEXTURE9* textures;
	};
}

#endif