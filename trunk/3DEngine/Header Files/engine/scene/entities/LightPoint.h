#ifndef LIGHTPOINT_H_
#define LIGHTPOINT_H_

#include "..\Entity.h"

namespace engine
{
	/**
	 * Represents a light in the world
	 */
	class LightPoint : public Entity
	{
	private:
		float range;
	public:
		LightPoint();
		~LightPoint();
		void CleanUp();

		void Update();
		void Draw(Renderer* argPRenderer);

		void SetRange(float argRange);
		float GetRange();
	};
}

#endif