#ifndef SCENE_H_
#define SCENE_H_

#include <map>
#include <list>
#include <string>
#include <iostream>
#include "..\logger\Logger.h"
#include "..\kernel\ResourceManager.h"
#include "..\renderer\Renderer.h"
#include "Heightmap.h"
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

		Heightmap* pHeightmap;
		Camera* pCamera;
		std::map<std::string, Model*> models;

		std::list<std::string> scripts;
		void ParseAndExecuteScript(std::string argScript);
	public:
		Scene();
		~Scene();
		void CleanUp();

		virtual void Update();
		virtual void Draw(Renderer* argPRenderer);

		void AddWindow(Window* argPWindow);
		void RemoveWindow(Window* argPWindow);
		std::list<Window*> GetWindows();

		Heightmap* GetHeightmap();
		Camera* GetCamera();
		
		Model* GetModel(std::string argModelName);
		std::map<std::string, Model*> GetModels();
		void AddModel(std::string argModelName, Model* argPModel);
		void RemoveModel(std::string argModelName);
		
		void AddScript(std::string argScript);
	};
}

#endif