#ifndef ENTITY_H_
#define ENTITY_H_

#include "Vector3.h"
#include "Renderer.h"

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
	public:
		virtual void Update()=0;
		virtual void Draw(Renderer* argPRenderer)=0;
		virtual void SetPosition(Vector3 argPosition)=0;
	};
}

#endif