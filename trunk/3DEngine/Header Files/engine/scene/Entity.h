#ifndef ENTITY_H_
#define ENTITY_H_

#include <map>
#include <list>
#include <vector>
#include <string>
#include <d3dx9.h>
#include "..\logger\Logger.h"
#include "Drawable.h"
#include "..\input\InputListener.h"
#include "..\utils\Vector3.h"
#include "..\utils\explode.h"
#include "..\renderer\Renderer.h"

namespace engine
{
	/**
	 * The Entity class is a representation of an object in a game or program.
	 * This class is responsible for drawing and updating itself on the screen.
	 * Class is abstract becuase entities will created via this template
	 */
	class Entity : public Drawable, public InputListener
	{
	private:
	protected:
		D3DXMATRIXA16 matWorld;
		Vector3 position;
		Vector3 rotation;
		Vector3 scaling;
		
		std::list<std::string> scripts;
		std::map<std::string, Entity*> entities;
		void ParseAndExecuteScript(std::string argScript);
	public:
		Entity();
		virtual ~Entity();
		virtual void CleanUp();

		virtual void Update();
		virtual void Draw(Renderer* argPRenderer);

		virtual void InputEvent(std::string argBind, float argSpeed);

		void SetPosition(Vector3 argPosition);
		void SetRotation(Vector3 argRotation);
		void SetScaling(Vector3 argScaling);

		Vector3 GetPosition();
		Vector3 GetRotation();
		Vector3 GetScaling();
		
		void AddScript(std::string argScript);
		Entity* GetEntity(std::string argEntityName);
		void AddEntity(std::string argEntityName, Entity* argPEntity);
	};
}

#endif