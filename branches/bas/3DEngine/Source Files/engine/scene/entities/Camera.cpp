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

		D3DXVECTOR3 vecEyePoint(this->position.x, this->position.y, this->position.z);
		D3DXVECTOR3 vecLookAt(	this->position.x + (sin(this->rotation.y) * cos(this->rotation.x)),
								this->position.y - (sin(this->rotation.x)),
								this->position.z + (cos(this->rotation.y) * cos(this->rotation.x)));
		D3DXVECTOR3 vecUp(0.0f, 1.0f, 0.0f);
		D3DXMatrixLookAtLH(&this->matWorld, &vecEyePoint, &vecLookAt, &vecUp);
		// Multiplies the entity world matrix with the renderer's world matrix (this->matWorld * renderer->matWorld)
		argPRenderer->AddToViewMatrix(&this->matWorld);


		// Apply the matrix transformations
		argPRenderer->TransformWorldMatrix();
		argPRenderer->TransformViewMatrix();
		argPRenderer->TransformProjectionMatrix();

		// The the camera as the OpenAL Listener
		ALfloat alPos[]		= { this->position.x, this->position.y, this->position.z };
		alListenerfv(AL_POSITION, alPos);
		ALfloat alVel[]		= { this->speed.x, this->speed.y, this->speed.z };
		alListenerfv(AL_VELOCITY, alVel);
		ALfloat alOri[]		= { -(sin(this->rotation.y) * cos(this->rotation.x)), (sin(this->rotation.x)), -(cos(this->rotation.y) * cos(this->rotation.x)), 0.0f, 1.0f, 0.0f };
		alListenerfv(AL_ORIENTATION, alOri);
	}

	/**
	 * Processes any input events
	 * @param		std::string		the bind to execute
	 * @param		float			the speed
	 * @return		void
	 */
	void Camera::InputEvent(std::string argBind, float argSpeed)
	{
		// For certain events the camera needs to reverse the speed
		if(	argBind == "move_forward" ||
			argBind == "move_backward" ||
			argBind == "move_forward_backward" ||
			argBind == "move_left" ||
			argBind == "move_right" ||
			argBind == "move_left_right" ||
			argBind == "pan_up" ||
			argBind == "pan_down" ||
			argBind == "pan_up_down")
		{
			argSpeed *= -1.0f;
		}
		
		// The max rotation we can allow on the x axis
		float threshold = (D3DX_PI / 2) - 0.1f;
		// We can't overturn the x axis or wierd stuff happens
		if(	argBind == "pan_up" ||
			argBind == "pan_down" ||
			argBind == "pan_up_down")
		{
			if(this->rotation.x > threshold && argSpeed < 0.0f)
			{
				argSpeed = 0.0f;
			}
			else if(this->rotation.x < -threshold && argSpeed > 0.0f)
			{
				argSpeed = 0.0f;
			}
		}

		Entity::InputEvent(argBind, argSpeed);
	}
}