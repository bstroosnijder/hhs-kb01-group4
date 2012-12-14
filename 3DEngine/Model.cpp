#include "Model.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Constructs the Scene object, initialising the Window and Entity collection.
	 */
	Model::Model(char* argPModelName)
	{
		Entity::Entity();
		this->pModelName = argPModelName;
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
	}

	/**
	 * Default implementation of the Load method for all entities
	 * @param		ResourceManager*		The resource manager to use.
	 * @param		Renderer*				The renderer to use.
	 * @return		void
	 */
	void Model::Load(ResourceManager* argPResourceManager, Renderer* argPRenderer)
	{
		this->SetResource(argPResourceManager->LoadResource(argPRenderer, this->pModelName));
		for each(Model* pModel in this->models)
		{
			pModel->Load(argPResourceManager, argPRenderer);
		}
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
		LPD3DXMESH mesh = this->resource->GetMesh();
		D3DMATERIAL9* pMeshMaterials = this->resource->GetMaterials();
		LPDIRECT3DTEXTURE9* pMeshTextures = this->resource->GetTextures();

		for(unsigned long i = 0; i < this->resource->GetNumMaterials(); i++)
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
		this->resource = argPResource;
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