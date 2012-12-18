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
	SceneManager::SceneManager()
	{
		engine::Logger::Log("Creating SceneManager", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
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
	
	Scene* SceneManager::LoadScene(std::string argSceneName, std::string argSceneFileName)
	{
		Logger::Log("Loading scenefile: " + argSceneFileName, Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		
		Scene* pScene = new Scene();
		this->scenes[argSceneName] = pScene;

		char line[256];

		// Parse the correct file name
		std::string fileName = std::string("Resource Files\\Scenes\\" + argSceneFileName);
		std::ifstream inStream (fileName);

		if(!inStream.is_open())
		{
			Logger::Log("Failed to open scenefile", Logger::LOG_LEVEL_ERROR, __FILE__, __LINE__);
		}

		// Camera settings
		Logger::Log("Getting Camera settings", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		inStream.getline(line, sizeof(line));
		std::vector<char*> values = explode(';', line);
		Camera* pCamera = pScene->GetCamera();
		pCamera->SetPosition(	Vector3((float)std::atof(values.at(0)),
										(float)std::atof(values.at(1)),
										(float)std::atof(values.at(2))));
		pCamera->SetRotation(	Vector3((float)std::atof(values.at(3)),
										(float)std::atof(values.at(4)),
										(float)std::atof(values.at(5))));
		pCamera->SetScaling(	Vector3((float)std::atof(values.at(6)),
										(float)std::atof(values.at(7)),
										(float)std::atof(values.at(8))));

		// Models
		Logger::Log("Getting Models", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		while(inStream.getline(line, sizeof(line)) != NULL)
		{
			std::vector<char*> values = explode(';', line);

			Model* pModel = new Model(values.at(10));
			pScene->AddModel(pModel);

			pModel->SetPosition(Vector3((float)std::atof(values.at(1)),
										(float)std::atof(values.at(2)),
										(float)std::atof(values.at(3))));
			pModel->SetRotation(Vector3((float)std::atof(values.at(4)),
										(float)std::atof(values.at(5)),
										(float)std::atof(values.at(6))));
			pModel->SetScaling(	Vector3((float)std::atof(values.at(7)),
										(float)std::atof(values.at(8)),
										(float)std::atof(values.at(9))));

			for(unsigned long i = 11; i < values.size(); i++)
			{
				// pModel->SetTexture();
			}
		}




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
