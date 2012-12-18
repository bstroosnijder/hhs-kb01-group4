#include "ResourceManager.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Constructs the ResourceManager object.
	 */
	ResourceManager::ResourceManager()
	{
		this->resources = std::map<std::string, Resource*>();
	}

	/**
	 * Destructs the ResourceManager object.
	 * @return		void
	 */
	ResourceManager::~ResourceManager()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void ResourceManager::CleanUp()
	{
	}

	LPDIRECT3DTEXTURE9 ResourceManager::LoadTexture(Renderer* argPRenderer, char* argPTextureName)
	{
		Logger::Log("Loading Texture:", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		Logger::Log(argPTextureName, Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);

		if(this->textures.count(std::string(argPTextureName)) > 0)
		{
			Logger::Log("Texture Already in Memory", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
			return this->textures[std::string(argPTextureName)];
		}
		
		if (!this->FileExists(argPTextureName))
		{
			Logger::Log("Texture not found:", Logger::LOG_LEVEL_WARNING, __FILE__, __LINE__);
			Logger::Log(argPTextureName, Logger::LOG_LEVEL_WARNING, __FILE__, __LINE__);			
		}
		DirectX9Renderer* pRenderer = (DirectX9Renderer*)argPRenderer;

		LPDIRECT3DTEXTURE9 texture;
		D3DXCreateTextureFromFileA(pRenderer->GetDevice(), argPTextureName, &texture);
		this->textures[std::string(argPTextureName)] = texture;

		return texture;
	}

	/**
	 * Loads a resource using it's file name and converting it into a Resource object.
	 * @param		Renderer*	The renderer to use
	 * @param		char*		The model name
	 * @return		Resource*
	 */
	Resource* ResourceManager::LoadResource(Renderer* argPRenderer, char* argPModelName)
	{
		engine::Logger::Log("Loading Resource:", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		engine::Logger::Log(argPModelName, Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		// this checks if the resource exists
		//Resource* r = this->resources[argPModelName];
		if(this->resources.count(std::string(argPModelName)) > 0)
		{
			engine::Logger::Log("Resource Already in Memory", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
			return this->resources[std::string(argPModelName)];
		}

		LPD3DXMESH mesh;
		D3DMATERIAL9* pMeshMaterials;
		LPDIRECT3DTEXTURE9* pMeshTextures;
		unsigned long numMaterials;

		LPD3DXBUFFER pD3DMaterialsBuffer;
		DirectX9Renderer* pRenderer = (DirectX9Renderer*)argPRenderer;

			
		// Load model from .x file
		D3DXLoadMeshFromX(	argPModelName, D3DXMESH_SYSTEMMEM, pRenderer->GetDevice(),
							NULL, &pD3DMaterialsBuffer, NULL, &numMaterials,
							&mesh);

		D3DXMATERIAL* pD3DXMaterials = (D3DXMATERIAL*)pD3DMaterialsBuffer->GetBufferPointer();

		pMeshMaterials = new D3DMATERIAL9[numMaterials];
		pMeshTextures = new LPDIRECT3DTEXTURE9[numMaterials];

		// Loop through materials and create textures
		for(unsigned long i = 0; i < numMaterials; i++)
		{
			pMeshMaterials[i] = pD3DXMaterials[i].MatD3D;
			pMeshMaterials[i].Ambient = pMeshMaterials[i].Diffuse;

			// Create texture from file
			if (this->FileExists(pD3DXMaterials[i].pTextureFilename))
			{
				D3DXCreateTextureFromFileA(	pRenderer->GetDevice(), pD3DXMaterials[i].pTextureFilename,
										&pMeshTextures[i]);
			}
			else
			{
				pMeshTextures[i] = NULL;
				Logger::Log("Texture not found:", Logger::LOG_LEVEL_WARNING, __FILE__, __LINE__);
				Logger::Log(pD3DXMaterials[i].pTextureFilename, Logger::LOG_LEVEL_WARNING, __FILE__, __LINE__);
				
			}
			this->textures[std::string(pD3DXMaterials[i].pTextureFilename)] = pMeshTextures[i];
		}
		
		Resource* pResource = new Resource();
		pResource->SetMesh(mesh);
		pResource->SetMaterials(pMeshMaterials);
		pResource->SetTextures(pMeshTextures);
		pResource->SetNumMaterials(numMaterials);
		this->resources[std::string(argPModelName)]= pResource;
		
		
		pD3DMaterialsBuffer->Release();
		engine::Logger::Log("Resource Loaded", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		return pResource;
	}
	
	Resource* ResourceManager::GetResource(char* argPResourceName)
	{
		return this->resources[std::string(argPResourceName)];
	}

	/**
	 * Checks if the parameter filename exists
	 * @param		const string&		ArgFilename The filename to check
	 * @return		bool
	 */
	bool ResourceManager::FileExists(const std::string& argFilename)
	{
    struct stat buf;
    if (stat(argFilename.c_str(), &buf) != -1)
		{
			return true;
		}
    return false;
	}
}
