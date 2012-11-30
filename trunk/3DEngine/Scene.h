#include <vector>
#include <algorithm>
#include <iostream>
#include "Entity.h"

namespace engine
{
	/**
	 * The Scene class is a representation of a 'level' or something similar, in the game this engine is running on.
	 * This class is responsible for maintaining and managing the entities inside him.
	 * This class is also responsible for calling upon all his entities to draw and/or update themselves.
	 */
	class Scene
	{
	private:
		std::vector<Entity*> entities;
	public:
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