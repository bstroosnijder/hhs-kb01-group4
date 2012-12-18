#ifndef ENTITY_H_
#define ENTITY_H_

#include "..\utils\Vector3.h"
#include "..\renderer\DirectX9Renderer.h"

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
		D3DXMATRIXA16 matWorld;
		Vector3 position;
		Vector3 rotation;
		Vector3 scaling;
	public:
		Entity();
		virtual ~Entity();
		virtual void CleanUp();

		virtual void Update();
		virtual void Draw(Renderer* argPRenderer);

		void SetPosition(Vector3 argPosition);
		void SetRotation(Vector3 argRotation);
		void SetScaling(Vector3 argScaling);

		Vector3 GetPosition();
		Vector3 GetRotation();
		Vector3 GetScaling();
	};
}

#endif