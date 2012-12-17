#include "Entity.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Constructs the Scene object, initialising the Window and Entity collection.
	 */
	Entity::Entity()
	{
		this->SetScaling(Vector3(1.0f, 1.0f, 1.0f));
	}

	/**
	 * Destructs the Scene object.
	 */
	Entity::~Entity()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing this object.
	 * @return		void
	 */
	void Entity::CleanUp()
	{
		Logger::Log("Disposing Entityy", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
	}

	/**
	 * Default implementation of the Update method for all entities
	 * @return		void
	 */
	void Entity::Update()
	{
	}

	/**
	 * Default implementation of the Draw method for all entities
	 * @param		Renderer*				The renderer to use.
	 * @return		void
	 */
	void Entity::Draw(Renderer* argPRenderer)
	{
		DirectX9Renderer* pRenderer = (DirectX9Renderer*)argPRenderer;
		D3DXMatrixIdentity(&this->matWorld);

		
		// Scaling
		D3DXMATRIXA16 matScaling;
		D3DXMatrixScaling(&matScaling, this->scaling.x, this->scaling.y, this->scaling.z);
		D3DXMatrixMultiply(&this->matWorld, &this->matWorld, &matScaling);
		
		// Rotation X
		D3DXMATRIXA16 matRotationX;
		D3DXMatrixRotationX(&matRotationX, this->rotation.x);
		D3DXMatrixMultiply(&this->matWorld, &this->matWorld, &matRotationX);
		// Rotation Y
		D3DXMATRIXA16 matRotationY;
		D3DXMatrixRotationY(&matRotationY, this->rotation.y);
		D3DXMatrixMultiply(&this->matWorld, &this->matWorld, &matRotationY);
		// Rotation Z
		D3DXMATRIXA16 matRotationZ;
		D3DXMatrixRotationZ(&matRotationZ, this->rotation.z);
		D3DXMatrixMultiply(&this->matWorld, &this->matWorld, &matRotationZ);

		// Position
		D3DXMATRIXA16 matPosition;
		D3DXMatrixTranslation(&matPosition, this->position.x, this->position.y, this->position.z);
		D3DXMatrixMultiply(&this->matWorld, &this->matWorld, &matPosition);

		// Multiplies the entity world matrix with the renderer's world matrix (this->matWorld * renderer->matWorld)
		pRenderer->AddToWorldMatrix(&this->matWorld);


		// Apply the matrix transformations
		pRenderer->TransformWorldMatrix();
		pRenderer->TransformViewMatrix();
		pRenderer->TransformProjectionMatrix();
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
	 * Getter for the position
	 * @return		Vector3					The position of the entity
	 */
	Vector3 Entity::GetPosition()
	{
		return this->position;
	}
	
	/**
	 * Getter for the rotation
	 * @return		Vector3					The rotation of the entity
	 */
	Vector3 Entity::GetRotation()
	{
		return this->rotation;
	}
	
	/**
	 * Getter for the rotation
	 * @return		Vector3					The scaling of the entity
	 */
	Vector3 Entity::GetScaling()
	{
		return this->scaling;
	}
}