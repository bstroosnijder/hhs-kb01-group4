#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <algorithm>
#include <iostream>
#include <algorithm>
#include "Entity.h"
#include "Camera.h"
#include "Renderer.h"

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
		std::vector<Window*> windows;
		std::vector<Entity*> entities;
	public:
		Scene();
		~Scene();
		void CleanUp();
		
		void Update();
		void Draw(Renderer* argPRenderer);

		void AddWindow(Window* argPWindow);
		void RemoveWindow(Window* argPWindow);
		Window* GetWindow(int argIndex);
		std::vector<Window*> GetWindows();
		void AddEntity(Entity* argPEntity);
		void RemoveEntity(Entity* argPEntity);
		Entity* GetEntity(int argIndex);
		std::vector<Entity*> GetEntities();
	};
}

#endif