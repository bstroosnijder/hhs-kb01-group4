#ifndef MODEL_H_
#define MODEL_H_

#include <map>
#include <string>
#include "..\..\logger\Logger.h"
#include "..\Entity.h"
#include "..\..\kernel\ResourceManager.h"
#include "..\..\renderer\Renderer.h"

namespace engine
{
	/**
	 * An entity with meshes and textures
	 */
	class Model : public Entity
	{
	private:
		Resource* pResource;
	public:
		Model(Resource* argPResource);
		~Model();
		void CleanUp();

		void Update();
		void Draw(Renderer* argPRenderer);

		void SetResource(Resource* argPResource);
		void SetTexture(unsigned long argIndex, LPDIRECT3DTEXTURE9 argTexture);
	};
}

#endif