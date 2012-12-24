#ifndef MODEL_H_
#define MODEL_H_

#include <map>
#include "..\..\logger\Logger.h"
#include "..\Entity.h"
#include "..\..\input\InputObserver.h"
#include "..\..\input\KeyboardState.h"
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
	public:
		Model(Resource* argPResource);
		~Model();
		void CleanUp();

		void Update();
		void Draw(Renderer* argPRenderer);

		void Notify(KeyboardState* argPKeyboardState);

		void SetResource(Resource* argPResource);
		void SetTexture(unsigned long argIndex, LPDIRECT3DTEXTURE9 argTexture);
		void AddModel(std::string argModelName, Model* argPModel);
	};
}

#endif