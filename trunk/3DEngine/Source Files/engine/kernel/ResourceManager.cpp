#include "..\..\..\Header Files\engine\kernel\ResourceManager.h"

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
		this->textures = std::map<std::string, LPDIRECT3DTEXTURE9>();
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

	/**
	 * Gets a texture by name
	 * @param		std::string				The name of the texture to get
	 * @return		LPDIRECT3DTEXTURE9
	 */
	LPDIRECT3DTEXTURE9 ResourceManager::GetTexture(std::string argTextureFileName)
	{
		return this->textures[argTextureFileName];
	}

	/**
	 * Loads a texture to be used later on meshes
	 * @param		Renderer*				The renderer to use for loading the texture on
	 * @param		std::string				The filename of the texture
	 * @return		LPDIRECT3DTEXTURE9
	 */
	LPDIRECT3DTEXTURE9 ResourceManager::LoadTexture(Renderer* argPRenderer, std::string argTextureFileName)
	{
		Logger::Log("Loading texture: " + argTextureFileName, Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);

		if(this->textures.count(argTextureFileName) > 0)
		{
			Logger::Log("Texture already in memory", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
			return this->textures[std::string(argTextureFileName)];
		}

		// Parse the correct file name
		std::string fileName = std::string("Resource Files\\Textures\\" + argTextureFileName);
		// Check if the texture exists
		if (!fileExists(fileName))
		{
			Logger::Log("Cannot find texture: " + fileName, Logger::LOG_LEVEL_WARNING, __FILE__, __LINE__);
			return NULL;
			return NULL;
		}


		DirectX9Renderer* pRenderer = (DirectX9Renderer*)argPRenderer;

		LPDIRECT3DTEXTURE9 texture;
		D3DXCreateTextureFromFileA(pRenderer->GetDevice(), fileName.c_str(), &texture);
		this->textures[argTextureFileName] = texture;

		return texture;
	}

	/**
	 * Gets a texture by name
	 * @param		std::string				The name of the texture to get
	 * @return		LPDIRECT3DTEXTURE9
	 */
	Resource* ResourceManager::GetResource(std::string argResourceFileName)
	{
		return this->resources[argResourceFileName];
	}

	/**
	 * Loads a resource using it's file name and converting it into a Resource object.
	 * @param		Renderer*				The renderer to use
	 * @param		std::string				The model name
	 * @return		Resource*
	 */
	Resource* ResourceManager::LoadResource(Renderer* argPRenderer, std::string argResourceFileName)
	{
		engine::Logger::Log("Loading resource: " + argResourceFileName, Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);

		// this checks if the resource exists
		if(this->resources.count(argResourceFileName) > 0)
		{
			Logger::Log("Resource already in memory", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
			return this->resources[argResourceFileName];
		}

		LPD3DXMESH mesh;
		D3DMATERIAL9* pMeshMaterials;
		LPDIRECT3DTEXTURE9* pMeshTextures;
		unsigned long numMaterials;

		LPD3DXBUFFER pD3DMaterialsBuffer;
		DirectX9Renderer* pRenderer = (DirectX9Renderer*)argPRenderer;

		
		// Parse the correct file name
		std::string fileName = std::string("Resource Files\\Models\\" + argResourceFileName);
		// Check if the resource exists
		if(!fileExists(fileName))
		{
			Logger::Log("Cannot find resource: " + fileName, Logger::LOG_LEVEL_ERROR, __FILE__, __LINE__);
			return NULL;
		}

		// Load model from .x file
		D3DXLoadMeshFromX(	fileName.c_str(), D3DXMESH_SYSTEMMEM, pRenderer->GetDevice(),
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

			this->LoadTexture(argPRenderer, pD3DXMaterials[i].pTextureFilename);
			pMeshTextures[i] = this->textures[std::string(pD3DXMaterials[i].pTextureFilename)];
		}
		
		Resource* pResource = new Resource();
		pResource->SetMesh(mesh);
		pResource->SetMaterials(pMeshMaterials);
		pResource->SetTextures(pMeshTextures);
		pResource->SetNumMaterials(numMaterials);
		this->resources[argResourceFileName]= pResource;
		
		
		pD3DMaterialsBuffer->Release();
		Logger::Log("Resource loaded", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		return pResource;
	}
}
