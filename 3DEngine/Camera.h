#ifndef CAMERA_H_
#define CAMERA_H_

#include "Entity.h"

namespace engine
{
	/**
	 * The camera class is the camera where we will see trought
	 * @author Alex Hodes
	 */
	class Camera : public Entity
	{
	private:
		Vector3 lookAt;
		Vector3 upVec;
	public:
		Camera();
		Camera(Vector3 argPosition, Vector3 argLookAt, Vector3 argUpVec);
		~Camera();
		void CleanUp();
		void Update();
		void Draw(Renderer* argPRenderer);
		void SetPosition(Vector3 argPosition);
		Vector3 GetPosition();
		void SetLookAt(Vector3 argLookAt);
		Vector3 GetLookAt();
		void SetUpVec(Vector3 argUpVec);
		Vector3 GetUpVec();
	};
}

#endif