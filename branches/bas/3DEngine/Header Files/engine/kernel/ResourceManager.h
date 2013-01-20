#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <map>
#include <string>
#include <d3dX9.h>
#include "..\logger\Logger.h"
#include "..\utils\explode.h"
#include "..\utils\fileExists.h"
#include "..\renderer\Renderer.h"
#include "..\resource\Resource.h"
#include "..\resource\Mesh.h"
#include "..\utils\WavFile.h"

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
		std::map<std::string, WavFile*> wavs;
	public:
		ResourceManager();
		~ResourceManager();
		void CleanUp();

		Mesh* GetMesh(std::string argMeshFileName);
		bool LoadMesh(Renderer* argPRenderer, std::string argMeshFileName);

		LPDIRECT3DTEXTURE9 GetTexture(std::string argTextureFileName);
		bool LoadTexture(Renderer* argPRenderer, std::string argTextureFileName);

		WavFile* GetWav(std::string argWavFileName);
		bool LoadWav(std::string argWavFileName);

		Resource* NewResource(std::string argMeshFileName);
	};
}

#endif