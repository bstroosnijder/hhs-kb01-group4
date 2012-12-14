#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <map>
#include <d3dx9.h>
#include "DirectX9Renderer.h"
#include <sys/stat.h>
#include "Resource.h"
#include "Logger.h"

namespace engine
{
	/**
	 * This class is responsible for the textures and models.
	 */
	class ResourceManager
	{
	private:
		//std::map<char*, Model*> models;
		std::map<char*, LPDIRECT3DTEXTURE9> textures;
		std::map<char*, Resource*> resources;
		bool FileExists(const std::string& filename);
	public:
		ResourceManager();
		~ResourceManager();
		void CleanUp();

		LPDIRECT3DTEXTURE9 LoadTexture(Renderer* argPRenderer, char* argPTextureName);
		Resource* LoadResource(Renderer* argPRenderer, char* argPModelName);

		Resource* GetResource(char* argPSceneName);
		//std::map<char*, Resource*> GetResources();
		//Resource* NewResource(char* argPSceneName);
		//void RemoveResource(char* argPSceneName);
	};
}

#endif