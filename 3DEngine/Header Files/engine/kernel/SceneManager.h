#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include "..\utils\explode.h"
#include "..\scene\Scene.h"

namespace engine
{
	/**
	 * The SceneManager is responsible for all the scenes that the engine contains or will contain.
	 */
	class SceneManager
	{
	private:
		std::map<std::string, Scene*> scenes;
	public:
		SceneManager();
		~SceneManager();
		void CleanUp();
		
		int GetSceneCount();
		Scene* GetScene(std::string argSceneName);
		std::map<std::string, Scene*> GetScenes();

		void AddScene(std::string argSceneName, Scene* argPScene);
		Scene* LoadScene(std::string argSceneName, std::string argSceneFileName);
		void RemoveScene(std::string argSceneName);
	};
}

#endif