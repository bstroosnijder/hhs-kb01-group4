#ifndef BENCH_H_
#define BENCH_H_

#include "Entity.h"

namespace engine
{
	class Bench: public Entity
	{
	private:
		float speed;
	public:
		Bench();
		~Bench();
		void CleanUp();
		
		void Load(ResourceManager* argPResourceManager, Renderer* argPRenderer);
		void Update();
		void Draw(Renderer* argPRenderer);
	};
}

#endif