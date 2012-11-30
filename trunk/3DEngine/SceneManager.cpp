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
		scenes = std::vector<Scene*>();
	}

	/**
	 * Destruct the SceneManager object.
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
	 * @param		index					The index in the collection by which to obtain the Scene pointer.
	 * @return		scene					The Scene at the given index, NULL returned if no scene exists on the given index.
	 */
	Scene* SceneManager::GetScene(int index)
	{
		return scenes.at(index);
	}

	/**
	 * Obtain all the Scene pointers in the scenes collection.
	 * @return		std::vector<Scene*>		The entire scene collection.
	 */
	std::vector<Scene*> SceneManager::GetScenes()
	{
		return scenes;
	}
	
	/**
	 */
	Scene* SceneManager::NewScene()
	{
		Scene* scene = new Scene();
		this->scenes.push_back(scene);
		return scene;
	}

	/**
	 * Remove a Scene pointer from the scenes collection.
	 * @param		Scene*					The Scene pointer to remove from the collection of scenes.
	 * @return		void
	 */
	void SceneManager::RemoveScene(Scene* argPScene)
	{
		//Find the position of the given scene and store it in 'position'.
		//Position is set equal to scenes.end() when the object can't be found.
		std::vector<Scene*>::iterator position = std::find(this->scenes.begin(), this->scenes.end(), argPScene);

		if(position != this->scenes.end()) 
		{
			this->scenes.erase(position);
		}
	}
}
