#ifndef TIGER_H_
#define TIGER_H_

#include "Entity.h"

namespace engine
{
	class Tiger : public Entity
	{
	public:
		Tiger();
		~Tiger();
		void CleanUp();
		
		void Load(ResourceManager* argPResourceManager, Renderer* argPRenderer);
		void Update();
		void Draw(Renderer* argPRenderer);
	};
}

#endif