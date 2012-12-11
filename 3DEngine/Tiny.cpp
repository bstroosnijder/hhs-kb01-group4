#include "Tiny.h"

namespace engine
{
	Tiny::Tiny()
	{
	}

	Tiny::~Tiny()
	{
		this->CleanUp();
	}

	void Tiny::CleanUp()
	{
	}
	
	void Tiny::Load(ResourceManager* argPResourceManager, Renderer* argPRenderer)
	{
		this->SetResource(argPResourceManager->LoadResource(argPRenderer, "tiny.x"));
	}

	void Tiny::Update()
	{
	}

	void Tiny::Draw(Renderer* argPRenderer)
	{
		argPRenderer->SetupMatricis();
		DirectX9Renderer* pRenderer = (DirectX9Renderer*)argPRenderer;

		LPD3DXMESH mesh = this->resource->GetMesh();
		D3DMATERIAL9* pMeshMaterials = this->resource->GetMaterials();
		LPDIRECT3DTEXTURE9* pMeshTextures = this->resource->GetTextures();

		for(unsigned long i = 0; i < this->resource->GetNumMaterials(); i++)
		{
			pRenderer->GetDevice()->SetMaterial(&pMeshMaterials[i]);
			pRenderer->GetDevice()->SetTexture(0, pMeshTextures[i]);
			mesh->DrawSubset(i);
		}
	}
}