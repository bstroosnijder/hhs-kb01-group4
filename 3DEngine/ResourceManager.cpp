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
		this->resources = std::map<char*, Resource*>();
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

	/**
	 * Loads a resource using it's file name and converting it into a Resource object.
	 * @param		Renderer*	The renderer to use
	 * @param		char*		The model name
	 * @return		Resource*
	 */
	Resource* ResourceManager::LoadResource(Renderer* argPRenderer, char* argPModelName)
	{
		engine::Logger::Log("Loading Resource", 1, __FILE__,__LINE__);
		// this checks if the resource exists
		if(this->resources.find(argPModelName) != this->resources.end())
		{
			engine::Logger::Log("Resource Already in Memory", 1, __FILE__,__LINE__);
			return this->resources[argPModelName];
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
			if (FileExists(pD3DXMaterials[i].pTextureFilename))
			{
				D3DXCreateTextureFromFileA(	pRenderer->GetDevice(), pD3DXMaterials[i].pTextureFilename,
										&pMeshTextures[i]);
			}
			else
			{
				pMeshTextures[i] = NULL;
				Logger::Log("Texture not found " , Logger::LOG_LEVEL_WARNING , __FILE__, __LINE__);
				// moet nog een logger aan gesproken worden
				
			}
		}
		
		Resource* pResource = new Resource();
		pResource->SetMesh(mesh);
		pResource->SetMaterials(pMeshMaterials);
		pResource->SetTextures(pMeshTextures);
		pResource->SetNumMaterials(numMaterials);
		this -> resources[argPModelName]= pResource;
		
		
		pD3DMaterialsBuffer->Release();
		engine::Logger::Log("Resource Loaded", 1, __FILE__,__LINE__);
		return pResource;
	}

	/**
	 * Loads a resource using the model and texture provided.
	 * @param		Renderer*	The renderer to use
	 * @param		char*		The model name
	 * @param		char*		The texture name
	 * @return		Resource*
	 */
	Resource* ResourceManager::LoadResource(Renderer* argPRenderer, char* argPModelName, char* argPTextureName)
	{
		return new Resource();
	}

	
	
	Resource* ResourceManager::GetResource(char* argPResourceName)
	{
		return this->resources[argPResourceName];
	}
	/*
	std::map<char*, Resource*> ResourceManager::GetResources()
	{
		return this->resources;
	}

	Resource* ResourceManager::NewResource(char* argPResourceName)
	{
		this->resources[argPSceneName] = new Resource();
	}

	void ResourceManager::RemoveResource(char* argPResourceName)
	{
		this->resources.erase(argPSceneName);
	}
	*/

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
