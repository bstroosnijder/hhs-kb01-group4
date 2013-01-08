#ifndef MODEL_H_
#define MODEL_H_

#include <map>
#include <string>
#include "..\..\logger\Logger.h"
#include "..\Entity.h"
#include "..\..\input\InputObserver.h"
#include "..\..\input\KeyboardState.h"
#include "..\..\input\MouseState.h"
#include "..\..\kernel\ResourceManager.h"
#include "..\..\renderer\Renderer.h"

namespace engine
{
	/**
	 * An entity with meshes and textures
	 */
	class Model : public Entity, public InputObserver
	{
	private:
		Resource* pResource;
		std::map<std::string, Model*> models;
		void PerformBind(std::string argBind, long argMouseSpeed);
	public:
		Model(Resource* argPResource);
		~Model();
		void CleanUp();

		void Update();
		void Draw(Renderer* argPRenderer);

		void Notify(std::map<std::string, std::string> argKeybinds, KeyboardState* argPKeyboardState,
					std::map<std::string, std::string> argMouseKeybinds, MouseState* argPMouseState);

		void SetResource(Resource* argPResource);
		void SetTexture(unsigned long argIndex, LPDIRECT3DTEXTURE9 argTexture);
		Model* GetModel(std::string argModelName);
		void AddModel(std::string argModelName, Model* argPModel);
	};
}

#endif