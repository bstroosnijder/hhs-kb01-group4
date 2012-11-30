#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include <vector>
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
		std::vector<Scene*> scenes;
	public:
		SceneManager();
		~SceneManager();
		void CleanUp();
		
		int GetWindowCount();
		Scene* GetScene(int index);
		std::vector<Scene*> GetScenes();
		Scene* NewScene();
		void RemoveScene(Scene* argPScene);
	};
}

#endif