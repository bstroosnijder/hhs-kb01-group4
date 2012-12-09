#ifndef ENTITY_H_
#define ENTITY_H_

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
		Resource* resource;
	public:
		virtual void Load(ResourceManager* argPResourceManager, Renderer* argPRenderer)=0;
		virtual void Update()=0;
		virtual void Draw(Renderer* argPRenderer)=0;

		void SetPosition(Vector3 argPosition);
		void SetResource(Resource* argPResource);
	};
}

#endif