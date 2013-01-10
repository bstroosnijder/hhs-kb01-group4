#ifndef MODEL_H_
#define MODEL_H_

#include <map>
#include <string>
#include "..\..\logger\Logger.h"
#include "..\Entity.h"
#include "..\..\input\listeners\KeyboardListener.h"
#include "..\..\input\KeyboardState.h"
#include "..\..\input\listeners\MouseListener.h"
#include "..\..\input\MouseState.h"
#include "..\..\input\listeners\JoyStickListener.h"
#include "..\..\input\JoyStickState.h"
#include "..\..\kernel\ResourceManager.h"
#include "..\..\renderer\Renderer.h"

namespace engine
{
	/**
	 * An entity with meshes and textures
	 */
	class Model : public Entity, public KeyboardListener, public MouseListener, public JoyStickListener
	{
	private:
		Resource* pResource;
		std::map<std::string, Model*> models;

		void DoBind(std::string argBind, long argSpeed);
	public:
		Model(Resource* argPResource);
		~Model();
		void CleanUp();
		
		void DoKeyboardEvent(std::map<std::string, std::string> argBinds, KeyboardState* argPState);
		void DoMouseEvent(std::map<std::string, std::string> argBinds, MouseState* argPState);
		void DoJoyStickEvent(std::map<std::string, std::string> argBinds, JoyStickState* argPState);

		void Update();
		void Draw(Renderer* argPRenderer);

		void SetResource(Resource* argPResource);
		void SetTexture(unsigned long argIndex, LPDIRECT3DTEXTURE9 argTexture);
		Model* GetModel(std::string argModelName);
		void AddModel(std::string argModelName, Model* argPModel);
	};
}

#endif