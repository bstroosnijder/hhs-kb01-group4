#include "Camera.h"

//---Private attributes---
//---Public attributes---
//---Private methods---
//---Public methods---

namespace engine
{
	/**
	 * Empty constructor Camera
	 * No idea why we have this
	 */
	Camera::Camera()
	{
	}
	/**
	 * Construct Camera
	 * @param		int		argX		The X location for the camera
	 * @param		int		argY		The Y location for the camera
	 * @param		int		argZ		The Z location for the cemara
	 * @param		int		argLookAtX	The X location where to look at
	 * @param		int		argLookAtY	The Y location where to look at
	 * @param		int		argLookAtZ	The Z location where to look at
	 * @param		int		argUpVecX	The X location how to tilt and go bezerk
	 * @param		int		argUpVecY	The Y location how to tilt and go bezerk
	 * @param		int		argUpVecZ	The Z location how to tilt and go bezerk
	 */
	Camera::Camera( int argX, int argY, int argZ ,
					int argLookAtX, int argLookAtY, int argLookAtZ, 
					int argUpVecX, int argUpVecY, int argUpVecZ )
	{
		x = argX;
		y = argY; 
		z = argZ;
		lookAtX = argLookAtX;
		lookAtY = argLookAtY;
		lookAtZ = argLookAtZ;
		upVecX = argUpVecX;
		upVecY = argUpVecY;
		upVecZ = argUpVecZ;
	}

	/**
	 * Empty destructor Camera
	 */
	Camera::~Camera()
	{
	}

	/**
	 * Draw does nothing yet
	 */
	void Camera::Draw(Renderer* argPRenderer)
	{

	}

	/**
	 * Update does nothing yet
	 */
	void Camera::Update()
	{
	}
}
