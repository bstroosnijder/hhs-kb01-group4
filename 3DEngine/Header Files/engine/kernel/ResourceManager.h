#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <map>
#include <string>
#include <d3dx9.h>
#include "..\utils\fileExists.h"
#include "..\logger\Logger.h"
#include "..\renderer\DirectX9Renderer.h"
#include "..\resource\Resource.h"

namespace engine
{
	/**
	 * This class is responsible for the textures and models.
	 */
	class ResourceManager
	{
	private:
		std::map<std::string, LPDIRECT3DTEXTURE9> textures;
		std::map<std::string, Resource*> resources;
	public:
		ResourceManager();
		~ResourceManager();
		void CleanUp();

		LPDIRECT3DTEXTURE9 GetTexture(std::string argTextureFileName);
		LPDIRECT3DTEXTURE9 LoadTexture(Renderer* argPRenderer, std::string argTextureFileName);

		Resource* GetResource(std::string argResourceFileName);
		Resource* LoadResource(Renderer* argPRenderer, std::string argResourceFileName);
	};
}

#endif