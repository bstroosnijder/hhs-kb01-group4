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

	void Camera::Notify(std::map<std::string, std::string> argKeybinds, KeyboardState* argPKeyboardState)
	{
		float speed = 0.025f;

		std::map<std::string, std::string>::iterator keybindsIt;
		for(keybindsIt = argKeybinds.begin(); keybindsIt != argKeybinds.end(); keybindsIt++)
		{
			std::string key		= keybindsIt->first;
			std::string bind	= keybindsIt->second;

			if(argPKeyboardState->IsKeyDown(key))
			{
				// Move Forward
				if(bind == "move_forward")
				{
					this->position.x += sin(this->rotation.y);
					//this->position.y -= sin(this->rotation.x);
					this->position.z += cos(this->rotation.y);
				}
				// Move Backward
				else if(bind == "move_backward")
				{
					this->position.x -= sin(this->rotation.y);
					//this->position.y += sin(this->rotation.x);
					this->position.z -= cos(this->rotation.y);
				}
				// Move Left
				else if(bind == "move_left")
				{
					this->position.x += sin(this->rotation.y - (D3DX_PI / 2));
					//this->position.y -= sin(this->rotation.x);
					this->position.z += cos(this->rotation.y - (D3DX_PI / 2));
				}
				// Move Right
				else if(bind == "move_right")
				{
					this->position.x -= sin(this->rotation.y - (D3DX_PI / 2));
					//this->position.y += sin(this->rotation.x);
					this->position.z -= cos(this->rotation.y - (D3DX_PI / 2));
				}
				// Move Up
				else if(bind == "move_up")
				{
					this->position.y += speed * 20;
				}
				// Move Down
				else if(bind == "move_down")
				{
					this->position.y -= speed * 20;
				}
				// Turn Left
				else if(bind == "turn_left")
				{
					this->rotation.y -= speed;
				}
				// Turn Right
				else if(bind == "turn_right")
				{
					this->rotation.y += speed;
				}

				// Reset
				else if(bind == "reset")
				{
					this->position = Vector3(0.0f, 0.0f, 0.0f);
					this->rotation = Vector3(0.0f, 0.0f, 0.0f);
					this->scaling  = Vector3(1.0f, 1.0f, 1.0f);
				}
			}
		}
	}
}