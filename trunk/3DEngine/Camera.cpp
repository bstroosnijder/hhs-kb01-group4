#include "Camera.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Constructs the Camera object.
	 */
	Camera::Camera() 
		: Entity()
	{
	}

	/**
	 * Destructs the Camera object.
	 */
	Camera::~Camera()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing this object.
	 * @return		void
	 */
	void Camera::CleanUp()
	{
		Logger::Log("Disposing Camera", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
	}

	void Camera::Update()
	{
		Entity::Update();
	}

	void Camera::Draw(Renderer* argPRenderer)
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
		
		D3DXMatrixInverse(&this->matWorld, NULL, &this->matWorld);
		// Multiplies the entity world matrix with the renderer's world matrix (this->matWorld * renderer->matWorld)
		pRenderer->AddToWorldMatrix(&this->matWorld);


		// Apply the matrix transformations
		pRenderer->TransformWorldMatrix();
		pRenderer->TransformViewMatrix();
		pRenderer->TransformProjectionMatrix();
	}
}