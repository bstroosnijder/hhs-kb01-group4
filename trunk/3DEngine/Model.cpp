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
		: Entity()
	{
		//Entity::Entity();
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
		Logger::Log("Disposing Model:", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		Logger::Log(this->pModelName, Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
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

		//LPDIRECT3DTEXTURE9* textures = this->pResource->GetTextures();
		//textures[0] = argPResourceManager->LoadTexture(argPRenderer, "banana.jpg");
		//this->pResource->SetTextures(textures);

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
		LPD3DXMESH mesh = this->pResource->GetMesh();
		D3DMATERIAL9* pMeshMaterials = this->pResource->GetMaterials();
		LPDIRECT3DTEXTURE9* pMeshTextures = this->pResource->GetTextures();

		for(unsigned long i = 0; i < this->pResource->GetNumMaterials(); i++)
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
	 * Adds an model
	 * @param		Model*					The model to add
	 * @return		void
	 */
	void Model::AddModel(Model* argPModel)
	{
		this->models.push_back(argPModel);
	}
}