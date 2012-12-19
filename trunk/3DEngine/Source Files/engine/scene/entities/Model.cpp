#include "..\..\..\..\Header Files\engine\scene\entities\Model.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Constructs the Scene object, initialising the Window and Entity collection.
	 */
	Model::Model(Resource* argPResource) : Entity()
	{
		this->pResource = argPResource;
	}
	
	/**
	 * Destructs the Scene object.
	 */
	Model::~Model()
	{
		this->CleanUp();
	}
	
	/**
	 * Lazy cleanup method for destructing this object.
	 * @return		void
	 */
	void Model::CleanUp()
	{
		Logger::Log("Disposing Model", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
	}

	/**
	 * Default implementation of the Update method for all entities
	 * @return		void
	 */
	void Model::Update()
	{
		Entity::Update();
	}

	/**
	 * Draw the model
	 * @param		Renderer*				The renderer to use.
	 * @return		void
	 */
	void Model::Draw(Renderer* argPRenderer)
	{
		Entity::Draw(argPRenderer);
		DirectX9Renderer* pRenderer = (DirectX9Renderer*)argPRenderer;

		// Get the mesh
		LPD3DXMESH mesh = this->pResource->pMesh->mesh;
		D3DMATERIAL9* pMeshMaterials = this->pResource->pMesh->materials;
		LPDIRECT3DTEXTURE9* pMeshTextures = this->pResource->textures;

		for(unsigned long i = 0; i < this->pResource->pMesh->numMaterials; i++)
		{
			pRenderer->GetDevice()->SetMaterial(&pMeshMaterials[i]);
			pRenderer->GetDevice()->SetTexture(0, pMeshTextures[i]);
			mesh->DrawSubset(i);
		}
		
		for each(Model* pModel in this->models)
		{
			argPRenderer->Push();
			pModel->Draw(argPRenderer);
			argPRenderer->Pop();
		}
	}

	/**
	 * Setter for the resource
	 * @param		Resource*				The new resource for the model
	 * @return		void
	 */
	void Model::SetResource(Resource* argPResource)
	{
		this->pResource = argPResource;
	}
	
	/**
	 * Sets a custom texture at the givin index in the resource
	 * @param		unsigned long		The index to put the texture at
	 * @param		LPDIRECT3DTEXTURE9	The texture to add at the index
	 * @return		void
	 */
	void Model::SetTexture(unsigned long argIndex, LPDIRECT3DTEXTURE9 argTexture)
	{
		this->pResource->textures[argIndex] = argTexture;
	}

	/**
	 * Adds an model
	 * @param		Model*					The model to add
	 * @return		void
	 */
	void Model::AddModel(Model* argPModel)
	{
		this->models.push_back(argPModel);
	}
}