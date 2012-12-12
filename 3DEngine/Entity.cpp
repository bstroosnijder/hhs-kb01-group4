#include "Entity.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Default implementation of the Load method for all entities
	 * @param		ResourceManager*		The resource manager to use.
	 * @param		Renderer*				The renderer to use.
	 * @return		void
	 */
	void Entity::Load(ResourceManager* argPResourceManager, Renderer* argPRenderer)
	{
		if(this->entities.size() > 0)
		{
			for each(Entity* pEntity in this->entities)
			{
				pEntity->Load(argPResourceManager, argPRenderer);
			}
		}
	}

	/**
	 * Default implementation of the Update method for all entities
	 * @return		void
	 */
	void Entity::Update()
	{
		if(this->entities.size() > 0)
		{
			for each(Entity* pEntity in this->entities)
			{
				pEntity->Update();
			}
		}
	}

	/**
	 * Default implementation of the Draw method for all entities
	 * @param		Renderer*				The renderer to use.
	 * @return		void
	 */
	void Entity::Draw(Renderer* argPRenderer)
	{
		DirectX9Renderer* pRenderer = (DirectX9Renderer*)argPRenderer;

		// Apply the matrix transformations
		pRenderer->TransformWorldMatrix();
		pRenderer->TransformViewMatrix();
		pRenderer->TransformProjectionMatrix();

		// Get the mesh and
		LPD3DXMESH mesh = this->resource->GetMesh();
		D3DMATERIAL9* pMeshMaterials = this->resource->GetMaterials();
		LPDIRECT3DTEXTURE9* pMeshTextures = this->resource->GetTextures();

		for(unsigned long i = 0; i < this->resource->GetNumMaterials(); i++)
		{
			pRenderer->GetDevice()->SetMaterial(&pMeshMaterials[i]);
			pRenderer->GetDevice()->SetTexture(0, pMeshTextures[i]);
			mesh->DrawSubset(i);
		}

		if(this->entities.size() > 0)
		{
			for each(Entity* pEntity in this->entities)
			{
				argPRenderer->Push();
				pEntity->Draw(argPRenderer);
				argPRenderer->Pop();
			}
		}
	}

	/**
	 * Setter for the position
	 * @param		Vector3					The new position for the entity
	 * @return		void
	 */
	void Entity::SetPosition(Vector3 argPosition)
	{
		this->position = argPosition;
	}

	/**
	 * Setter for the rotation
	 * @param		Vector3					The new rotation for the entity
	 * @return		void
	 */
	void Entity::SetRotation(Vector3 argRotation)
	{
		this->rotation = argRotation;
	}

	/**
	 * Setter for the scaling
	 * @param		Vector3					The new scaling for the entity
	 * @return		void
	 */
	void Entity::SetScaling(Vector3 argScaling)
	{
		this->scaling = argScaling;
	}

	/**
	 * Setter for the resource
	 * @param		Resource*				The new resource for theentity
	 * @return		void
	 */
	void Entity::SetResource(Resource* argPResource)
	{
		this->resource = argPResource;
	}

	/**
	 * Adds an entity
	 * @param		Entity*					The entity to add
	 * @return		void
	 */
	void Entity::AddEntity(Entity* argPEntity)
	{
		this->entities.push_back(argPEntity);
	}
}