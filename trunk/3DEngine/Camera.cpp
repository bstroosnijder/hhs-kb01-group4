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
		//Empty constructor because we're oblidged to implement it..
	}

	/**
	 * Construct Camera
	 * @param		Vector3		The location Vector3
	 * @param		Vector3		The Vector3 that determines where to look at
	 * @param		Vector3		The Vector3 that goes bezerk
	 */
	Camera::Camera(Vector3 argPosition, Vector3 argLookAt, Vector3 argUpVec)
	{
		this->position = argPosition;
		this->lookAt = argLookAt;
		this->upVec = argUpVec;
	}

	/**
	 * Destructs the Camera object.
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
	 * TODO: More information.
	 * @return		void
	 */
	void Camera::Update()
	{

	}

	/**
	 * TODO: More information.
	 * @param		Renderer*		The renderer used to draw
	 * @return		void
	 */
	void Camera::Draw(Renderer* argPRenderer)
	{
	}

	/**
	 * Sets the position of the camera.
	 * @param		Vector3			The position that'll be assigned to the Camera object.
	 * @return		void
	 */
	void Camera::SetPosition(Vector3 argPosition)
	{
		this->position = argPosition;
	}

	/**
	 * Obtain the position of the camera.
	 * @return		Vector3
	 */
	Vector3 Camera::GetPosition()
	{
		return this->position;
	}

	/**
	 * Set the position where the Camera should look towards.
	 * @param		Vector3			The position to where the Camera should look towards.
	 * @return		void
	 */
	void Camera::SetLookAt(Vector3 argLookAt)
	{
		this->lookAt = argLookAt;
	}

	/**
	 * Obtain the position that the Camera is looking towards.
	 * @return		Vector3
	 */
	Vector3 Camera::GetLookAt()
	{
		return this->lookAt;
	}

	/**
	 * Set the pan-degree of the Camera.
	 * @param		Vector3			The degree of panning for the Camera.
	 * @return		void
	 */
	void Camera::SetUpVec(Vector3 argUpVec)
	{
		this->upVec = argUpVec;
	}

	/**
	 * Get the pan-degree of the Camera.
	 * @return		Vector3			The degree of panning for the Camera.
	 */
	Vector3 Camera::GetUpVec()
	{
		return this->upVec;
	}
}
