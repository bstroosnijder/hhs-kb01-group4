#include "..\..\..\Header Files\engine\kernel\SceneManager.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Construct the SceneManager object.
	 */
	SceneManager::SceneManager(ResourceManager* argPResourceManager)
	{
		engine::Logger::Log("Creating SceneManager", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		this->pResourceManager = argPResourceManager;
		this->scenes = std::map<std::string, Scene*>();
	}

	/**
	 * Destructs the SceneManager object.
	 * @return		void
	 */
	SceneManager::~SceneManager()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void SceneManager::CleanUp()
	{
	}

	/**
	 * Returns the number of scenes currently in the scenes vector
	 * @return		int
	 */
	int SceneManager::GetSceneCount()
	{
		return this->scenes.size();
	}

	/**
	 * Obtain the Scene pointer using an index.
	 * @param		std::string					The index name in the collection by which to obtain the Scene pointer.
	 * @return		Scene*						The Scene at the given index, NULL returned if no scene exists on the given index.
	 */
	Scene* SceneManager::GetScene(std::string argSceneName)
	{
		Logger::Log("Geting scene:" + argSceneName, Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		return this->scenes.at(argSceneName);
	}

	/**
	 * Obtain all the Scene pointers in the scenes collection.
	 * @return		std:map<std::string, Scene*>		The entire scene collection.
	 */
	std::map<std::string, Scene*> SceneManager::GetScenes()
	{
		return this->scenes;
	}

	/**
	 * Add a scene to the scene collection within the Scene manager
	 * @deprecated
	 * @param		std::string				argPSceneName is the identifier for the scene in the collection
	 * @param		Scene*					Scene is the scene that will be added to the scene collection
	*/
	void SceneManager::AddScene(std::string argSceneName, Scene* argPScene)
	{
		Logger::Log("Adding scene: " + argSceneName, Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		this->scenes[argSceneName] = argPScene;
		Logger::Log("Scene " + argSceneName + " added", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
	}
	
	Scene* SceneManager::LoadScene(Renderer* argPRenderer, std::string argSceneName, std::string argSceneFileName)
	{
		Logger::Log("Loading scenefile: " + argSceneFileName, Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		
		// Create a new scene object to load the data of the scenefile in
		Scene* pScene = new Scene();
		this->scenes[argSceneName] = pScene;
		
		// Parse the correct file name
		std::string fileName = std::string("Resource Files\\Scenes\\" + argSceneFileName);
		// Check if the texture exists
		if (!fileExists(fileName))
		{
			Logger::Log("Cannot find scenefile: " + fileName, Logger::LOG_LEVEL_ERROR, __FILE__, __LINE__);
			return NULL;
		}

		// Create an input stream on the scene file so we can read from it
		std::ifstream inStream (fileName);
		// Check if the scene file has opened
		if(!inStream.is_open())
		{
			Logger::Log("Failed to open scenefile", Logger::LOG_LEVEL_ERROR, __FILE__, __LINE__);
		}

		// Keep track of the current segment so that we know what to do with each line
		std::string curSegment;
		while(inStream.good())
		{
			char peek = inStream.peek();
			// The line buffer used to read lines from the file
			char cLine[256];
			inStream.getline(cLine, sizeof(cLine));
			// Convert line to a string because we use strings
			std::string line (cLine);

			if(peek == '#')
			{
				curSegment = line.substr(1);
				Logger::Log("Found segment: " + curSegment, Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
				// auto set the next line as the line so that we can handle it
				inStream.getline(cLine, sizeof(cLine));
				line = std::string(cLine);
			}

			// Skip empty lines (without continue ..)
			if(line.size() > 0)
			{
				std::vector<std::string> data = explode(';', line);
				//Logger::Log(line, Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);

				// Because switch case isn't supported with string :(
				if(curSegment == "camera")
				{
					Vector3 position	= Vector3(	(float)std::atof(data.at(0).c_str()),
													(float)std::atof(data.at(1).c_str()),
													(float)std::atof(data.at(2).c_str()));
					Vector3 rotation	= Vector3(	(float)std::atof(data.at(3).c_str()),
													(float)std::atof(data.at(4).c_str()),
													(float)std::atof(data.at(5).c_str()));
					Vector3 scaling		= Vector3(	(float)std::atof(data.at(6).c_str()),
													(float)std::atof(data.at(7).c_str()),
													(float)std::atof(data.at(8).c_str()));
					
					Camera* pCamera = pScene->GetCamera();
					pCamera->SetPosition(position);
					pCamera->SetRotation(rotation);
					pCamera->SetScaling(scaling);
				}
				else if(curSegment == "resources")
				{
					std::string resourceType		= data.at(0);
					std::string resourceFileName	= data.at(1);

					if(resourceType == "model")
					{
						this->pResourceManager->LoadResource(argPRenderer,resourceFileName);
					}
					else if(resourceType == "texture")
					{
						this->pResourceManager->LoadTexture(argPRenderer, resourceFileName);
					}
					else
					{
						Logger::Log("Resource type unsupported: " + resourceType, Logger::LOG_LEVEL_WARNING, __FILE__, __LINE__);
					}
				}
				else if(curSegment == "models")
				{
					std::string modelName		= data.at(0);
					std::string modelResource	= data.at(10);
					Vector3 position			= Vector3(	(float)std::atof(data.at(1).c_str()),
															(float)std::atof(data.at(2).c_str()),
															(float)std::atof(data.at(3).c_str()));
					Vector3 rotation			= Vector3(	(float)std::atof(data.at(4).c_str()),
															(float)std::atof(data.at(5).c_str()),
															(float)std::atof(data.at(6).c_str()));
					Vector3 scaling				= Vector3(	(float)std::atof(data.at(7).c_str()),
															(float)std::atof(data.at(8).c_str()),
															(float)std::atof(data.at(9).c_str()));

					Model* pModel = new Model(this->pResourceManager->GetResource(modelResource));
					pScene->AddModel(modelName, pModel);
					pModel->SetPosition(position);
					pModel->SetRotation(rotation);
					pModel->SetScaling(scaling);

					// todo: custom textures
					for(unsigned long i = 11; i < data.size(); i++)
					{
						pModel->SetTexture((i - 11), this->pResourceManager->GetTexture(data.at(i)));
					}
				}
				else
				{
					Logger::Log("Segment unsupported", Logger::LOG_LEVEL_WARNING, __FILE__, __LINE__);
				}
			}
		}







		// Porperly close the scene file
		inStream.close();
		Logger::Log("Scenefile loaded: " + argSceneFileName, Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		return pScene;
	}

	/**
	 * Remove a Scene pointer from the scenes collection.
	 * @param		std::string					The index name to remove from the collection of scenes.
	 * @return		void
	 */
	void SceneManager::RemoveScene(std::string argSceneName)
	{
		engine::Logger::Log("Removing Scene: " + argSceneName, Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		this -> scenes.erase(argSceneName);
	}
}
