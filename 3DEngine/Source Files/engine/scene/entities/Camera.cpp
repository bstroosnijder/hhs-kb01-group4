#include "..\..\..\..\Header Files\engine\scene\entities\Camera.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Constructs the Camera object.
	 */
	Camera::Camera() : Entity()
	{
	}

	/**
	 * Destructs the Camera object.
	 */
	Camera::~Camera()
	{
		Logger::Log("Camera: Disposing", Logger::INFO, __FILE__, __LINE__);
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing this object.
	 * @return		void
	 */
	void Camera::CleanUp()
	{
	}

	void Camera::Update()
	{
		Entity::Update();
	}

	void Camera::Draw(Renderer* argPRenderer)
	{
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
		argPRenderer->AddToWorldMatrix(&this->matWorld);

		// Apply the matrix transformations
		argPRenderer->TransformWorldMatrix();
		argPRenderer->TransformViewMatrix();
		argPRenderer->TransformProjectionMatrix();
	}

	void Camera::Notify(KeyboardState* argPKeyboardState)
	{
		float speed = 0.025f;
		// Move Forward
		if(argPKeyboardState->KEY_W)
		{
			this->position.x += sin(this->rotation.y);
			//this->position.y += sin(this->rotation.x);
			this->position.z += cos(this->rotation.y);
		}
		// Move Backward
		if(argPKeyboardState->KEY_S)
		{
			this->position.x -= sin(this->rotation.y);
			//this->position.y -= sin(this->rotation.x);
			this->position.z -= cos(this->rotation.y);
		}
		// Turn Left
		if(argPKeyboardState->KEY_A)
		{
			this->rotation.y -= speed;
		}
		// Turn Right
		if(argPKeyboardState->KEY_D)
		{
			this->rotation.y += speed;
		}
		// Move Left
		if(argPKeyboardState->KEY_Q)
		{
			this->position.x += sin(this->rotation.y - (D3DX_PI / 2));
			//this->position.y += sin(this->rotation.x);
			this->position.z += cos(this->rotation.y - (D3DX_PI / 2));
		}
		// Move Right
		if(argPKeyboardState->KEY_E)
		{
			this->position.x -= sin(this->rotation.y - (D3DX_PI / 2));
			//this->position.y -= sin(this->rotation.x);
			this->position.z -= cos(this->rotation.y - (D3DX_PI / 2));
		}
		// Move Up
		if(argPKeyboardState->KEY_LSHIFT)
		{
			this->position.y -= speed * 20;
		}
		// Move Down
		if(argPKeyboardState->KEY_SPACE)
		{
			this->position.y += speed * 20;
		}
		// Reset
		if(argPKeyboardState->KEY_HOME)
		{
			this->position = Vector3(0.0f, 0.0f, 0.0f);
			this->rotation = Vector3(0.0f, 0.0f, 0.0f);
			this->scaling  = Vector3(1.0f, 1.0f, 1.0f);
		}
	}
}