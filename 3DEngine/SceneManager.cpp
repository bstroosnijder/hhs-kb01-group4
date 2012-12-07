#include "SceneManager.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Construct the SceneManager object.
	 */
	SceneManager::SceneManager()
	{
		scenes = std::map<char*, Scene*>();
	}

	/**
	 * Destructs the SceneManager object.
	 * @return		void
	 */
	SceneManager::~SceneManager()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void SceneManager::CleanUp()
	{
	}

	/**
	 * Returns the number of scenes currently in the scenes vector
	 * @return		int
	 */
	int SceneManager::GetWindowCount()
	{
		return this->scenes.size();
	}

	/**
	 * Obtain the Scene pointer using an index.
	 * @param		char*		argPName	The index name in the collection by which to obtain the Scene pointer.
	 * @return		scene					The Scene at the given index, NULL returned if no scene exists on the given index.
	 */
	Scene* SceneManager::GetScene(char* argPName)
	{
		return scenes.at(argPName);
	}

	/**
	 * Obtain all the Scene pointers in the scenes collection.
	 * @return		std:mapo<char,Scene*>		The entire scene collection.
	 */
	std::map<char*, Scene*> SceneManager::GetScenes()
	{
		return this -> scenes;
	}
	
	/**
	 * Creates a new scene
	 * @param		char* argPName is a custom index name within the scenes collection. 
	 * @return		Scene*
	 */
	Scene* SceneManager::NewScene(char* argPName)
	{
		Scene* scene = new Scene();
		scenes[argPName] = scene;
		return scene;
	}

	/**
	 * Remove a Scene pointer from the scenes collection.
	 * @param		Scene*		argPName	The index name to remove from the collection of scenes.
	 * @return		void
	 */
	void SceneManager::RemoveScene(char* argPName)
	{
		this -> scenes.erase(argPName);
	}
}
