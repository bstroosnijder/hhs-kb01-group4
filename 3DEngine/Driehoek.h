#ifndef DRIEHOEK_H_
#define DRIEHOEK_H_

#include "Entity.h"

namespace engine
{
	class Driehoek : public Entity
	{
	public:
		Driehoek();
		~Driehoek();
		void CleanUp();
		void Update();
		void Draw(Renderer* argPRenderer);
		void SetPosition(Vector3 argPosition);
		Vector3 GetPosition();
	};
}

#endif