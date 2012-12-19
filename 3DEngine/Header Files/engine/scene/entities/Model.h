#ifndef MODEL_H_
#define MODEL_H_

#include <list>
#include <d3dx9.h>
#include "..\..\kernel\ResourceManager.h"
#include "..\Entity.h"

namespace engine
{
	class Model : public Entity
	{
	private:
		Resource* pResource;
		std::list<Model*> models;
	public:
		Model(Resource* argPResource);
		~Model();
		void CleanUp();

		void Update();
		void Draw(Renderer* argPRenderer);

		void SetResource(Resource* argPResource);
		void SetTexture(unsigned long argIndex, LPDIRECT3DTEXTURE9 argTexture);
		void AddModel(Model* argPModel);
	};
}

#endif