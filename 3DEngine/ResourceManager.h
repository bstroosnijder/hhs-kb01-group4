#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <map>
#include <d3dx9.h>
#include "DirectX9Renderer.h"
#include "Resource.h"

namespace engine
{
	/**
	 * This class is responsible for the textures and models.
	 */
	class ResourceManager
	{
	private:
		//std::map<char*, Model*> models;
		//std::map<char*, char*> textures;
		std::map<char*, Resource*> resources;
	public:
		ResourceManager();
		~ResourceManager();
		void CleanUp();
		Resource* LoadResource(Renderer* argPRenderer, char* argPModelName);
		Resource* LoadResource(Renderer* argPRenderer, char* argPModelName, char* argPTextureName);

		Resource* GetResource(char* argPSceneName);
		//std::map<char*, Resource*> GetResources();
		//Resource* NewResource(char* argPSceneName);
		//void RemoveResource(char* argPSceneName);
	};
}

#endif