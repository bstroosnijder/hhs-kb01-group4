#ifndef MODEL_H_
#define MODEL_H_

#include <map>
#include "..\..\logger\Logger.h"
#include "..\..\kernel\ResourceManager.h"
#include "..\..\renderer\Renderer.h"
#include "..\Entity.h"

namespace engine
{
	class Model : public Entity
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

		void SetResource(Resource* argPResource);
		void SetTexture(unsigned long argIndex, LPDIRECT3DTEXTURE9 argTexture);
		void AddModel(std::string argModelName, Model* argPModel);
	};
}

#endif