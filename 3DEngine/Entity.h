#ifndef ENTITY_H_
#define ENTITY_H_

#include <list>
#include "ResourceManager.h"
#include "Vector3.h"
#include "DirectX9Renderer.h"

namespace engine
{
	/**
	 * The Entity class is a representation of an object in a game or program.
	 * This class is responsible for drawing and updating itself on the screen.
	 * Class is abstract becuase entities will created via this template
	 * @author Alex Hodes
	 */
	class Entity
	{
	private:
	protected:
		Vector3 position;
		Vector3 rotation;
		Vector3 scaling;
		Resource* resource;
		std::list<Entity*> entities;
	public:
		virtual void Load(ResourceManager* argPResourceManager, Renderer* argPRenderer);
		virtual void Update();
		virtual void Draw(Renderer* argPRenderer);

		void SetPosition(Vector3 argPosition);
		void SetRotation(Vector3 argRotation);
		void SetScaling(Vector3 argScaling);
		void SetResource(Resource* argPResource);
		void AddEntity(Entity* argPEntity);
	};
}

#endif