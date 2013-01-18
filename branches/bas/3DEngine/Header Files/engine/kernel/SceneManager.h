#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include "..\logger\Logger.h"
#include "..\utils\explode.h"
#include "..\utils\fileExists.h"
#include "..\scene\Scene.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "..\input\InputDevice.h"
#include "..\input\InputListener.h"
#include "..\renderer\Renderer.h"

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

		Scene* NewScene(std::string argPSceneName);
		Scene* LoadScene(ResourceManager* argPResourceManager, InputManager* argPInputManager,
			Renderer* argPRenderer, std::string argSceneName, std::string argSceneFileName);
		void RemoveScene(std::string argSceneName);
	};
}

#endif