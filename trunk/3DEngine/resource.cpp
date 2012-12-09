#include "resource.h"

namespace engine
{
	/**
	 * This does nothing
	 */
	Resource::Resource()
	{
	}

	/**
	 * This does nothing
	 */
	Resource::~Resource()
	{
	}
	
	void Resource::SetMesh(LPD3DXMESH argMesh)
	{
		this->mesh = argMesh;
	}

	LPD3DXMESH Resource::GetMesh()
	{
		return this->mesh;
	}
	
	void Resource::SetMaterials(D3DMATERIAL9* argMaterials)
	{
		this->materials = argMaterials;
	}

	D3DMATERIAL9* Resource::GetMaterials()
	{
		return this->materials;
	}
	
	void Resource::SetTextures(LPDIRECT3DTEXTURE9* argTextures)
	{
		this->textures = argTextures;
	}

	LPDIRECT3DTEXTURE9* Resource::GetTextures()
	{
		return this->textures;
	}
	
	void Resource::SetNumMaterials(unsigned long argNumMaterials)
	{
		this->numMaterials = argNumMaterials;
	}

	unsigned long Resource::GetNumMaterials()
	{
		return this->numMaterials;
	}
}