#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <d3dx9.h>
#include "Mesh.h"

namespace engine
{
	/**
	 * Data container for a mesh and textures.
	 * This way we can keep meshes singleton in the resource manager, and overwrite it's textures via this struct
	 */
	struct Resource
	{
		Mesh* pMesh;
		LPDIRECT3DTEXTURE9* textures;
	};
}

#endif