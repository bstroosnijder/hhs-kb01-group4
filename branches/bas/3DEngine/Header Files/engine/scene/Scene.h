#ifndef SCENE_H_
#define SCENE_H_

#include <map>
#include <list>
#include <string>
#include <iostream>
#include "..\input\InputListener.h"
#include "..\logger\Logger.h"
#include "..\kernel\ResourceManager.h"
#include "..\renderer\Renderer.h"
#include "Skybox.h"
#include "Heightmap.h"
#include "entities\Camera.h"
#include "entities\Model.h"
#include "entities\LightPoint.h"
#include "entities\Sound.h"

namespace engine
{
	/**
	 * The Scene class is a representation of a 'level' or something similar, in the game this engine is running on.
	 * This class is responsible for maintaining and managing the entities inside him.
	 * This class is also responsible for calling upon all his entities to draw and/or update themselves.
	 */
	class Scene : public InputListener
	{
	private:
		bool loaded;
		bool running;
		std::list<Window*> windows;
		
		Camera* pCamera;
		Skybox* pSkybox;
		Heightmap* pHeightmap;
		std::map<std::string, Entity*> entities;

		std::list<std::string> scripts;
		void ParseAndExecuteScript(std::string argScript);
	public:
		Scene();
		~Scene();
		void CleanUp();

		bool isLoaded();
		void SetLoaded(bool argLoaded);

		virtual void Update();
		virtual void Draw(Renderer* argPRenderer);

		void InputEvent(std::string argBind, float argSpeed);

		void AddWindow(Window* argPWindow);
		void RemoveWindow(Window* argPWindow);
		std::list<Window*> GetWindows();
		
		Camera* GetCamera();
		Skybox* GetSkybox();
		void SetSkybox(Skybox* argPSkybox);
		Heightmap* GetHeightmap();
		void SetHeightmap(Heightmap* argPHeightmap);
		
		Entity* GetEntity(std::string argEntityName);
		std::map<std::string, Entity*> GetEntities();
		void AddEntity(std::string argEntityName, Entity* argPEntity);
		void RemoveEntity(std::string argEntityName);
		
		std::list<std::string> GetScripts();
		void AddScript(std::string argScript);
	};
}

#endif