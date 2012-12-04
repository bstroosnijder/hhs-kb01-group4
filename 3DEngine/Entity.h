#ifndef ENTITY_H_
#define ENTITY_H_

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
		int x;
		int y;
		int z; 
		//maybe a position matrix might be nessacery
	public:
		virtual void Draw(Renderer* argPRenderer) =0;
		//this method is not in the class diagram.
		virtual void Update()=0;
	};
}

#endif