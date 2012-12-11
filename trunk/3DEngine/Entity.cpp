#include "Entity.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Default implementation of the renderer
	 * @param		Renderer*		The renderer to use.
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
	}

	/**
	 * Setter for the position
	 * @param		Vector3		The new position for the entity
	 * @return		void
	 */
	void Entity::SetPosition(Vector3 argPosition)
	{
		this->position = argPosition;
	}

	/**
	 * Setter for the rotation
	 * @param		Vector3		The new rotation for the entity
	 * @return		void
	 */
	void Entity::SetRotation(Vector3 argRotation)
	{
		this->rotation = argRotation;
	}

	/**
	 * Setter for the scaling
	 * @param		Vector3		The new scaling for the entity
	 * @return		void
	 */
	void Entity::SetScaling(Vector3 argScaling)
	{
		this->scaling = argScaling;
	}

	/**
	 * Setter for the resource
	 * @param		Resource*	The new resource for theentity
	 * @return		void
	 */
	void Entity::SetResource(Resource* argPResource)
	{
		this->resource = argPResource;
	}
}