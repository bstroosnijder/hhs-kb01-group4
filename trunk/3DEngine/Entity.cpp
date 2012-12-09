#include "Entity.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Setter for the position
	 * @param		Vector3		The new position for the entity
	 * @return		void
	 */
	void Entity::SetPosition(Vector3 argPosition)
	{
		this->position = argPosition;
	}

	/**
	 * Setter for the resource
	 * @param		Resource*	The new resource for theentity
	 * @return		void
	 */
	void Entity::SetResource(Resource* argPResource)
	{
		this->resource = argPResource;
	}
}