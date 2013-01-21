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
		unsigned long index;
		bool enabled;
		D3DLIGHT9 light;

		float range;
		D3DXCOLOR color;
	public:
		LightPoint(unsigned long argIndex);
		~LightPoint();
		void CleanUp();

		void Update();
		void Draw(Renderer* argPRenderer);

		void SetIndex(unsigned long argIndex);
		unsigned long GetIndex();

		void SetRange(float argRange);
		float GetRange();

		D3DXCOLOR GetColor();
		void SetColor(float argColorR, float argColorG, float argColorB, float argColorA);
	};
}

#endif