#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include <map>
#include <algorithm>
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
		Scene* GetScene(char* argPName);
		std::map<char*, Scene*> GetScenes();
		Scene* NewScene(char* argPName);
		void RemoveScene(char* argPName);
	};
}

#endif