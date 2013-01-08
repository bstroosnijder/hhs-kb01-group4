#include "..\..\..\..\Header Files\engine\scene\entities\Camera.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---

	/**
	 * A method that performs the action corresponding to the bind
	 * @param		std::string		The bind to execute
	 * @param		int				mouse x
	 * @param		int				mouse y
	 * @return		void
	 */
	void Camera::PerformBind(std::string argBind, long argMouseSpeed)
	{
		float speed = 0.025f;
		if(argMouseSpeed > 0)
		{
			speed *= argMouseSpeed;
		}


		// Move Forward
		if(argBind == "move_forward")
		{
			this->position.x += sin(this->rotation.y);
			//this->position.y -= sin(this->rotation.x);
			this->position.z += cos(this->rotation.y);
		}
		// Move Backward
		else if(argBind == "move_backward")
		{
			this->position.x -= sin(this->rotation.y);
			//this->position.y += sin(this->rotation.x);
			this->position.z -= cos(this->rotation.y);
		}
		// Move Left
		else if(argBind == "move_left")
		{
			this->position.x += sin(this->rotation.y - (D3DX_PI / 2));
			//this->position.y -= sin(this->rotation.x);
			this->position.z += cos(this->rotation.y - (D3DX_PI / 2));
		}
		// Move Right
		else if(argBind == "move_right")
		{
			this->position.x -= sin(this->rotation.y - (D3DX_PI / 2));
			//this->position.y += sin(this->rotation.x);
			this->position.z -= cos(this->rotation.y - (D3DX_PI / 2));
		}
		// Move Up
		else if(argBind == "move_up")
		{
			this->position.y += speed * 20;
		}
		// Move Down
		else if(argBind == "move_down")
		{
			this->position.y -= speed * 20;
		}
		// Turn Left
		else if(argBind == "turn_left")
		{
			this->rotation.y -= speed;
		}
		// Turn Right
		else if(argBind == "turn_right")
		{
			this->rotation.y += speed;
		}
		// Pan Up
		else if(argBind == "pan_up")
		{
			this->rotation.x -= speed;
		}
		// Pan Down
		else if(argBind == "pan_down")
		{
			this->rotation.x += speed;
		}

		// Reset
		else if(argBind == "reset")
		{
			this->position = Vector3(0.0f, 0.0f, 0.0f);
			this->rotation = Vector3(0.0f, 0.0f, 0.0f);
			this->scaling  = Vector3(1.0f, 1.0f, 1.0f);
		}
	}

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

	/**
	 *
	 */
	void Camera::Update()
	{
		Entity::Update();
	}

	/**
	 *
	 */
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

	/**
	 *
	 */
	void Camera::Notify(std::map<std::string, std::string> argKeybinds, KeyboardState* argPKeyboardState,
						std::map<std::string, std::string> argMouseKeybinds, MouseState* argPMouseState)
	{
		std::map<std::string, std::string>::iterator keybindsIt;
		for(keybindsIt = argKeybinds.begin(); keybindsIt != argKeybinds.end(); keybindsIt++)
		{
			std::string key		= keybindsIt->first;
			std::string bind	= keybindsIt->second;

			if(argPKeyboardState->IsKeyDown(key))
			{
				this->PerformBind(bind, 0);
			}
		}

		std::map<std::string, std::string>::iterator mouseKeybindsIt;
		for(mouseKeybindsIt = argMouseKeybinds.begin(); mouseKeybindsIt != argMouseKeybinds.end(); mouseKeybindsIt++)
		{
			std::string key		= mouseKeybindsIt->first;
			std::string bind	= mouseKeybindsIt->second;

			if(argPMouseState->IsKeyDown(key))
			{
				this->PerformBind(bind, argPMouseState->GetMouseSpeed(key));
			}
		}
	}
}