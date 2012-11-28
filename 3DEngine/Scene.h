#include <vector>
#include <iostream>
#include <algorithm>
#include "Entity.h"

namespace engine
{
	class Scene
	{
	private:
		//---Private attributes---
		std::vector<Entity*> entities;
	public:
		//---Public methods---
		Scene();
		~Scene();
		void AddEntity(Entity* entity);
		void RemoveEntity(Entity* entity);
		Entity* GetEntity(int index);
		std::vector<Entity*> GetEntities();
		void Draw();
		void Update();
	};
}