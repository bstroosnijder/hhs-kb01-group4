#ifndef MODEL_H_
#define MODEL_H_

#include <list>
#include "Entity.h"
#include "ResourceManager.h"
#include <d3dx9.h>

namespace engine
{
	class Model : public Entity
	{
	private:
		char* pModelName;
		Resource* pResource;
		std::list<Model*> models;
	public:
		Model(char* argPModelName);
		~Model();
		void CleanUp();

		void Load(ResourceManager* argPResourceManager, Renderer* argPRenderer);
		void Update();
		void Draw(Renderer* argPRenderer);

		void SetResource(Resource* argPResource);
		void AddModel(Model* argPModel);
	};
}

#endif