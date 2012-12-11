#ifndef BARREL_H_
#define BARREL_H_

#include "Entity.h"

namespace engine
{
	class Barrel : public Entity
	{
	private:
		float speed;
	public:
		Barrel();
		~Barrel();
		void CleanUp();
		
		void Load(ResourceManager* argPResourceManager, Renderer* argPRenderer);
		void Update();
		void Draw(Renderer* argPRenderer);
	};
}

#endif