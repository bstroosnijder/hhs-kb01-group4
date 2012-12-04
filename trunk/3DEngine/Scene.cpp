#include "Scene.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Construct the Scene object.
	 */
	Scene::Scene()
	{
		this->windows = std::vector<Window*>();
		this->entities = std::vector<Entity*>();
	}

	/**
	 * Destruct the Scene object.
	 */
	Scene::~Scene()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void Scene::CleanUp()
	{
	}

	/**
	 * Update each entity in the entities collection.
	 * @return		void
	 */
	void Scene::Update()
	{
		for each(Entity* entity in entities)
		{
			entity->Update();
		}
	}

	/**
	 * Draw each entity in the entities collection.
	 * @param		Renderer*					argPRenderer is the current renderer to which the entity will draw
	 * @return		void
	 */
	void Scene::Draw(Renderer* argPRenderer)
	{
		for each(Entity* entity in entities)
		{
			entity->Draw(argPRenderer);
		}
		
	}

	/**
	 * Adds a window to the window list of the scene. the scene will render in these windows
	 * @param		Window*						The window to add to the scene
	 * @return		void
	 */
	void Scene::AddWindow(Window* argPWindow)
	{
		this->windows.push_back(argPWindow);
	}

	/**
	 * Removes a window from the window list of the scene
	 * @param		Window*						The window to remove
	 * @return		void
	 */
	void Scene::RemoveWindow(Window* argPWindow)
	{
	}

	/**
	 * Gets a window by index from the scene's window list
	 * @param		int							The index to get the window of
	 * @return		Window*
	 */
	Window* Scene::GetWindow(int argIndex)
	{
		return this->windows.at(argIndex);
	}

	/**
	 * Getter for the window list
	 * @return		std::vector<Window*>		The list of windows
	 */
	std::vector<Window*> Scene::GetWindows()
	{
		return this->windows;
	}

	/**
	 * Add an entity pointer to the list of entities.
	 * @param		entity						The Entity pointer to add to the collection of entities.
	 * @return		void
	 */
	void Scene::AddEntity(Entity* entity)
	{
		// TODO: zorgen dat cameras niet toegevoegd kunnen worden
		entities.push_back(entity);
	}

	/**
	 * Remove an entity pointer from the collection of entities.
	 * @param		entity						The entity pointer to remove from the collection of entities.
	 * @return		void
	 */
	void Scene::RemoveEntity(Entity* entity)
	{
		//Find the position of the given entity and store it in 'position'.
		//Position is set equal to entities.end() when the object can't be found.
		std::vector<Entity*>::iterator position = std::find(entities.begin(), entities.end(), entity);

		if(position != entities.end()) 
		{
			entities.erase(position);
		}
	}

	/**
	 * Obtain the Entity pointer using an index.
	 * @param		index						The index in the collection by which to obtain the entity pointer.
	 * @return		entity						The entity at the given index, NULL returned if no entity exists on the given index.
	 */
	Entity* Scene::GetEntity(int index)
	{
		return entities.at(index);
	}

	/**
	 * Obtain all the entity pointers in the entities collection.
	 * @return		std::vector<Entity*>		The entire entity collection.
	 */
	std::vector<Entity*> Scene::GetEntities()
	{
		return entities;
	}

	void Scene::SetCamera(Camera* argPCamera)
	{
		this->camera = argPCamera;
	}

	Camera* Scene::GetCamera()
	{
		return this->camera;
	}
}