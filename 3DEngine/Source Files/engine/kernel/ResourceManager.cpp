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
		this->meshes = std::map<std::string, Mesh*>();
		this->textures = std::map<std::string, LPDIRECT3DTEXTURE9>();
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
	 * Gets a mesh by name
	 * @param		std::string				The name of the mesh to get
	 * @return		Mesh*
	 */
	Mesh* ResourceManager::GetMesh(std::string argMeshFileName)
	{
		return this->meshes[argMeshFileName];
	}

	bool ResourceManager::LoadMesh(Renderer* argPRenderer, std::string argMeshFileName)
	{
		engine::Logger::Log("Loading mesh: " + argMeshFileName, Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);

		// this checks if the resource exists
		if(this->meshes.count(argMeshFileName) > 0)
		{
			Logger::Log("Mesh already in memory", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
			return true;
		}

		// Parse the correct file name
		std::string fileName = std::string("Resource Files\\Models\\" + argMeshFileName);
		// Check if the resource exists
		if(!fileExists(fileName))
		{
			Logger::Log("Cannot find mesh: " + fileName, Logger::LOG_LEVEL_ERROR, __FILE__, __LINE__);
			return false;
		}

		// The mesh object that stores all the info about the mesh so we can use this to render
		Mesh* pMesh = new Mesh();
		this->meshes[argMeshFileName] = pMesh;

		LPD3DXBUFFER pD3DMaterialsBuffer;
		DirectX9Renderer* pRenderer = (DirectX9Renderer*)argPRenderer;

		// Load model from .x file
		D3DXLoadMeshFromX(	fileName.c_str(), D3DXMESH_SYSTEMMEM, pRenderer->GetDevice(),
							NULL, &pD3DMaterialsBuffer, NULL, &pMesh->numMaterials,
							&pMesh->mesh);

		D3DXMATERIAL* pD3DXMaterials = (D3DXMATERIAL*)pD3DMaterialsBuffer->GetBufferPointer();

		pMesh->materials = new D3DMATERIAL9[pMesh->numMaterials];
		pMesh->textures = new LPDIRECT3DTEXTURE9[pMesh->numMaterials];

		// Loop through materials and create textures
		for(unsigned long i = 0; i < pMesh->numMaterials; i++)
		{
			pMesh->materials[i] = pD3DXMaterials[i].MatD3D;
			pMesh->materials[i].Ambient = pMesh->materials[i].Diffuse;

			this->LoadTexture(argPRenderer, pD3DXMaterials[i].pTextureFilename);
			pMesh->textures[i] = this->textures[std::string(pD3DXMaterials[i].pTextureFilename)];
		}
		
		
		pD3DMaterialsBuffer->Release();
		Logger::Log("Mesh loaded", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		return true;
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
	 * @return		bool
	 */
	bool ResourceManager::LoadTexture(Renderer* argPRenderer, std::string argTextureFileName)
	{
		Logger::Log("Loading texture: " + argTextureFileName, Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);

		if(this->textures.count(argTextureFileName) > 0)
		{
			Logger::Log("Texture already in memory", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
			return true;
		}

		// Parse the correct file name
		std::string fileName = std::string("Resource Files\\Textures\\" + argTextureFileName);
		// Check if the texture exists
		if (!fileExists(fileName))
		{
			Logger::Log("Cannot find texture: " + fileName, Logger::LOG_LEVEL_WARNING, __FILE__, __LINE__);
			return false;
		}


		DirectX9Renderer* pRenderer = (DirectX9Renderer*)argPRenderer;

		LPDIRECT3DTEXTURE9 texture;
		D3DXCreateTextureFromFileA(pRenderer->GetDevice(), fileName.c_str(), &texture);
		this->textures[argTextureFileName] = texture;

		return true;
	}

	Resource* ResourceManager::NewResource(std::string argMeshFileName)
	{
		Resource* pResource = new Resource();
		pResource->pMesh = this->GetMesh(argMeshFileName);

		// To make sure that each resource can have unique textures we have to make a new texture array
		// to separatly store the textures from the original
		pResource->textures = new LPDIRECT3DTEXTURE9[pResource->pMesh->numMaterials];
		for(unsigned long i = 0; i < pResource->pMesh->numMaterials; i++)
		{
			pResource->textures[i] = pResource->pMesh->textures[i];
		}

		return pResource;
	}
}
