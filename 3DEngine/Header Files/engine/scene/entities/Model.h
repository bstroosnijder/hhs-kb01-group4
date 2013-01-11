#ifndef MODEL_H_
#define MODEL_H_

#include <map>
#include <string>
#include "..\..\logger\Logger.h"
#include "..\Entity.h"
#include "..\..\input\InputListener.h"
#include "..\..\kernel\ResourceManager.h"
#include "..\..\renderer\Renderer.h"

namespace engine
{
	/**
	 * An entity with meshes and textures
	 */
	class Model : public Entity, public InputListener
	{
	private:
		Resource* pResource;
		std::map<std::string, Model*> models;

		void DoBind(std::string argBind, float argSpeed);
	public:
		Model(Resource* argPResource);
		~Model();
		void CleanUp();

		void Update();
		void Draw(Renderer* argPRenderer);

		void InputEvent(std::string argBind, float argSpeed);

		void SetResource(Resource* argPResource);
		void SetTexture(unsigned long argIndex, LPDIRECT3DTEXTURE9 argTexture);
		Model* GetModel(std::string argModelName);
		void AddModel(std::string argModelName, Model* argPModel);
	};
}

#endif