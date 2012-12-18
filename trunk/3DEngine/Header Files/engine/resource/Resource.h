#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <d3dx9.h>
#include "..\logger\Logger.h"

namespace engine
{
	/**
	 * This class is responsible for resource
	 * @author Alex Hodes
	 */
	class Resource
	{
	private:
		LPD3DXMESH mesh;
		D3DMATERIAL9* materials;
		LPDIRECT3DTEXTURE9* textures;
		unsigned long numMaterials;
	public:
		Resource();
		~Resource();
		void CleanUp();

		void SetMesh(LPD3DXMESH argMesh);
		LPD3DXMESH GetMesh();
		void SetMaterials(D3DMATERIAL9* argMaterials);
		D3DMATERIAL9* GetMaterials();
		void SetTextures(LPDIRECT3DTEXTURE9* argTextures);
		LPDIRECT3DTEXTURE9* GetTextures();
		void SetNumMaterials(unsigned long argNumMaterials);
		unsigned long GetNumMaterials();
	};
}
#endif