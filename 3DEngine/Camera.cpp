#include "Camera.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Empty constructor Camera
	 * No idea why we have this
	 */
	Camera::Camera()
	{
	}

	/**
	 * Construct Camera
	 * @param		Vector3		The location Vector3
	 * @param		Vector3		The Vector3 that determints where to look at
	 * @param		Vector3		The Vector3 that goes bezerk
	 */
	Camera::Camera(Vector3 argPosition, Vector3 argLookAt, Vector3 argUpVec)
	{
		this->position = argPosition;
		this->lookAt = argLookAt;
		this->upVec = argUpVec;
	}

	/**
	 * Empty destructor Camera
	 */
	Camera::~Camera()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void Camera::CleanUp()
	{
	}

	/**
	 * Update does nothing yet
	 * @return		void
	 */
	void Camera::Update()
	{
	}

	/**
	 * Draw does nothing yet
	 * @param		Renderer*		The renderer used to draw
	 * @return		void
	 */
	void Camera::Draw(Renderer* argPRenderer)
	{
	}

	//TODO: COMMENTS!
	void Camera::SetPosition(Vector3 argPosition)
	{
		this->position = argPosition;
	}

	Vector3 Camera::GetPosition()
	{
		return this->position;
	}

	void Camera::SetLookAt(Vector3 argLookAt)
	{
		this->lookAt = argLookAt;
	}

	Vector3 Camera::GetLookAt()
	{
		return this->lookAt;
	}

	void Camera::SetUpVec(Vector3 argUpVec)
	{
		this->upVec = argUpVec;
	}

	Vector3 Camera::GetUpVec()
	{
		return this->upVec;
	}
}
