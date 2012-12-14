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
	{
		this->SetScaling(Vector3(1.0f, 1.0f, 1.0f));
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
	}
}