#ifndef CAMERA_H_
#define CAMERA_H_

#include "Entity.h"

namespace engine
{
	class Camera : public Entity
	{
	public:
		Camera();
		~Camera();
		void CleanUp();

		void Update();
		void Draw(Renderer* argPRenderer);
	};
}

#endif