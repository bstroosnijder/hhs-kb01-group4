#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <list>

namespace engine
{
	/**
	 * This class is responsible for the textures and models.
	 */
	class ResourceManager
	{
	private:
		//std::map<char*, Resource*> resources;
	public:
		ResourceManager();
		~ResourceManager();
		void CleanUp();
		void LoadResource(char* argPResourceName);

		//Resource* GetResource(char* argPSceneName);
		//std::map<char*, Resource*> GetResources();
		//Resource* NewResource(char* argPSceneName);
		//void RemoveResource(char* argPSceneName);
	};
}

#endif