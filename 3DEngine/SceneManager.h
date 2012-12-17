#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "explode.h"
#include "Scene.h"

namespace engine
{
	/**
	 * The SceneManager is responsible for all the scenes that the engine contains or will contain.
	 */
	class SceneManager
	{
	private:
		std::map<char*, Scene*> scenes;
	public:
		SceneManager();
		~SceneManager();
		void CleanUp();
		
		int GetWindowCount();
		Scene* GetScene(char* argPSceneName);
		std::map<char*, Scene*> GetScenes();
		Scene* NewScene(char* argPSceneName);
		void AddScene(char* argPSceneName, Scene* argPScene);
		Scene* LoadScene(char* argPFileName);
		void RemoveScene(char* argPSceneName);
	};
}

#endif