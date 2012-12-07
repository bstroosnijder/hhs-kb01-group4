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
		//this->resources = std::map<char*, Resource*>();
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
	 * @param	argPResourceName	The file name of the resource.
	 * @return	void
	 */
	void LoadResource(char* argPResourceName)
	{

	}

	
	/*
	Resource* ResourceManager::GetResource(char* argPResourceName)
	{
		return this->resources[argPSceneName];
	}

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
}
