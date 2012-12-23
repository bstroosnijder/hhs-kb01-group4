#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <map>
#include <string>
#include <d3dx9.h>
#include "..\logger\Logger.h"
#include "..\utils\fileExists.h"
#include "..\renderer\Renderer.h"
#include "..\resource\Resource.h"
#include "..\resource\\Mesh.h"

namespace engine
{
	/**
	 * This class is responsible for the loading of the textures and the models,
	 * it makes sure that every resource is only loaded once.
	 */
	class ResourceManager
	{
	private:
		std::map<std::string, Mesh*> meshes;
		std::map<std::string, LPDIRECT3DTEXTURE9> textures;
	public:
		ResourceManager();
		~ResourceManager();
		void CleanUp();

		Mesh* GetMesh(std::string argMeshFileName);
		bool LoadMesh(Renderer* argPRenderer, std::string argMeshFileName);

		LPDIRECT3DTEXTURE9 GetTexture(std::string argTextureFileName);
		bool LoadTexture(Renderer* argPRenderer, std::string argTextureFileName);

		Resource* NewResource(std::string argMeshFileName);
	};
}

#endif