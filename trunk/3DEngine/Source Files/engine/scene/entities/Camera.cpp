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
		Logger::Log("Camera: Initializing", Logger::INFO, __FILE__, __LINE__);
		Logger::Log("Camera: Finished", Logger::INFO, __FILE__, __LINE__);
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
		//nothing to clean up here
	}

	/**
	 * Default implementation of the Update method for all entities
	 * @return		void
	 */
	void Camera::Update()
	{
		Entity::Update();
	}

	/**
	 * Draw the camera, adjust the world matrix to move around us
	 * @param		Renderer*				The renderer to use.
	 * @return		void
	 */
	void Camera::Draw(Renderer* argPRenderer)
	{
		// Reset our world matrix
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

	/**
	 * Processes any input events
	 * @param		std::string		the bind to execute
	 * @param		float			the speed
	 * @return		void
	 */
	void Camera::InputEvent(std::string argBind, float argSpeed)
	{
		// Move Forward
		if(argBind == "move_forward")
		{
			this->position.x += (sin(this->rotation.y) * argSpeed);
			//this->position.y -= (tan(this->rotation.x) * argSpeed);
			this->position.z += (cos(this->rotation.y) * argSpeed);
		}
		// Move Backward=
		else if(argBind == "move_backward")
		{
			this->position.x -= (sin(this->rotation.y) * argSpeed);
			//this->position.y += (tan(this->rotation.x) * argSpeed);
			this->position.z -= (cos(this->rotation.y) * argSpeed);
		}
		// =Move Forward or Backward
		else if(argBind == "move_forward_backward")
		{
			this->position.x -= (sin(this->rotation.y) * argSpeed);
			//this->position.y += (sin(this->rotation.x) * argSpeed);
			this->position.z -= (cos(this->rotation.y) * argSpeed);
		}
		// Move Left
		else if(argBind == "move_left")
		{
			this->position.x += (sin(this->rotation.y - (D3DX_PI / 2)) * argSpeed);
			//this->position.y -= (sin(this->rotation.x) * argSpeed);
			this->position.z += (cos(this->rotation.y - (D3DX_PI / 2)) * argSpeed);
		}
		// Move Right
		else if(argBind == "move_right")
		{
			this->position.x -= (sin(this->rotation.y - (D3DX_PI / 2)) * argSpeed);
			//this->position.y += (sin(this->rotation.x) * argSpeed);
			this->position.z -= (cos(this->rotation.y - (D3DX_PI / 2)) * argSpeed);
		}
		// Move Left or Right
		else if(argBind == "move_left_right")
		{
			this->position.x -= (sin(this->rotation.y - (D3DX_PI / 2)) * argSpeed);
			//this->position.y += (sin(this->rotation.x) * argSpeed);
			this->position.z -= (cos(this->rotation.y - (D3DX_PI / 2)) * argSpeed);
		}
		// Move Up
		else if(argBind == "move_up")
		{
			this->position.y += argSpeed;
		}
		// Move Down
		else if(argBind == "move_down")
		{
			this->position.y -= argSpeed;
		}
		// Turn Left
		else if(argBind == "turn_left")
		{
			this->rotation.y -= (float)(argSpeed / 10);
		}
		// Turn Right || Turn Left or Right
		else if(argBind == "turn_right" || argBind == "turn_left_right")
		{
			this->rotation.y += (float)(argSpeed / 10);
		}
		// Pan Up
		else if(argBind == "pan_up")
		{
			this->rotation.x -= (float)(argSpeed / 10);
		}
		// Pan Down || Pan Up or Down
		else if(argBind == "pan_down" || argBind == "pan_up_down")
		{
			this->rotation.x += (float)(argSpeed / 10);
		}

		// Reset
		else if(argBind == "reset")
		{
			this->position = Vector3(0.0f, 0.0f, 0.0f);
			this->rotation = Vector3(0.0f, 0.0f, 0.0f);
			this->scaling  = Vector3(1.0f, 1.0f, 1.0f);
		}
		// Use the default from entity
		else
		{
			Entity::InputEvent(argBind, argSpeed);
		}
	}
}