#ifndef TINY_H_
#define TINY_H_

#include "Entity.h"

namespace engine
{
	class Tiny : public Entity
	{
	public:
		Tiny();
		~Tiny();
		void CleanUp();
		
		void Load(ResourceManager* argPResourceManager, Renderer* argPRenderer);
		void Update();
		void Draw(Renderer* argPRenderer);
	};
}

#endif