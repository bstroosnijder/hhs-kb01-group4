#include "SceneManager.h"

namespace engine
{
	/**
	 * Construct the SceneManager object.
	*/
	SceneManager::SceneManager()
	{
		scenes = std::vector<Scene*>();
	}

	/**
	 * Destruct the SceneManager object.
	*/
	SceneManager::~SceneManager()
	{
		//Todo
	}

	/**
	 * Add a Scene pointer to the scenes collection.
	 * @param	scene		The Scene pointer to add to the collection of scenes.
	*/
	void SceneManager::AddScene(Scene* scene)
	{
		scenes.push_back(scene);
	}

	/**
	 * Remove a Scene pointer from the scenes collection.
	 * @param	scene		The Scene pointer to remove from the collection of scenes.
	*/
	void SceneManager::RemoveScene(Scene* scene)
	{
		//Find the position of the given scene and store it in 'position'.
		//Position is set equal to scenes.end() when the object can't be found.
		std::vector<Scene*>::iterator position = std::find(scenes.begin(), scenes.end(), scene);

		if(position != scenes.end()) 
		{
			scenes.erase(position);
		}
	}

	/**
	 * Obtain the Scene pointer using an index.
	 * @param	index		The index in the collection by which to obtain the Scene pointer.
	 * @return	scene		The Scene at the given index, NULL returned if no scene exists on the given index.
	*/
	Scene* SceneManager::GetScene(int index)
	{
		return scenes.at(index);
	}

	/**
	 * Obtain all the Scene pointers in the scenes collection.
	 * @return	scene		The entire scene collection.
	*/
	std::vector<Scene*> SceneManager::GetScenes()
	{
		return scenes;
	}
}
