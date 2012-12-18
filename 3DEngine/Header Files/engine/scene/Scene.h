#ifndef SCENE_H_
#define SCENE_H_

#include <list>
#include <iostream>
#include "..\kernel\ResourceManager.h"
#include "..\renderer\Renderer.h"
#include "entities\Camera.h"
#include "entities\Model.h"

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
		std::list<Window*> windows;

		Camera* pCamera;
		std::list<Model*> models;
	public:
		Scene();
		~Scene();
		void CleanUp();

		void Load(ResourceManager* argPResourceManager, Renderer* argPRenderer);
		virtual void Update();
		virtual void Draw(Renderer* argPRenderer);

		void AddWindow(Window* argPWindow);
		void RemoveWindow(Window* argPWindow);
		std::list<Window*> GetWindows();

		Camera* GetCamera();

		void AddModel(Model* argPModel);
		void RemoveModel(Model* argPModel);
		std::list<Model*> GetModels();
	};
}

#endif