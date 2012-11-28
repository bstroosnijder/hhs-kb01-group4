#include "Scene.h"

namespace engine
{
	//---Public methods---

	/**
	 * Construct the Scene object.
	*/
	Scene::Scene()
	{
		entities = std::vector<Entity*>();
	}

	/**
	 * Destruct the Scene object.
	*/
	Scene::~Scene()
	{
		//Todo
	}

	/**
	 * Add an entity pointer to the list of entities.
	 * @param	entity		The Entity pointer to add to the collection of entities.
	*/
	void Scene::AddEntity(Entity* entity)
	{
		entities.push_back(entity);
	}

	/**
	 * Remove an entity pointer from the collection of entities.
	 * @param	entity		The entity pointer to remove from the collection of entities.
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
	 * @param	index			The index in the collection by which to obtain the entity pointer.
	 * @return	entity			The entity at the given index, NULL returned if no entity exists on the given index.
	*/
	Entity* Scene::GetEntity(int index)
	{
		return entities.at(index);
	}

	/**
	 * Obtain all the entity pointers in the entities collection.
	 * @return	entities		The entire entity collection.
	*/
	std::vector<Entity*> Scene::GetEntities()
	{
		return entities;
	}

	/**
	 * Draw each entity in the entities collection.
	*/
	void Scene::Draw()
	{
		for each(Entity* entity in entities)
		{
			entity->Draw();
		}
	}

	/**
	 * Update each entity in the entities collection.
	*/
	void Scene::Update()
	{
		for each(Entity* entity in entities)
		{
			entity->Update();
		}
	}
}