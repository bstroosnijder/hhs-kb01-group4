#include "SceneManager.h"

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
		scenes = std::map<char*, Scene*>();
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
	int SceneManager::GetWindowCount()
	{
		return this->scenes.size();
	}

	/**
	 * Obtain the Scene pointer using an index.
	 * @param		char*		argPName		The index name in the collection by which to obtain the Scene pointer.
	 * @return		scene						The Scene at the given index, NULL returned if no scene exists on the given index.
	 */
	Scene* SceneManager::GetScene(char* argPSceneName)
	{
		Logger::Log("Geting scene", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		return scenes.at(argPSceneName);
	}

	/**
	 * Obtain all the Scene pointers in the scenes collection.
	 * @return		std:mapo<char*, Scene*>		The entire scene collection.
	 */
	std::map<char*, Scene*> SceneManager::GetScenes()
	{
		return this -> scenes;
	}
	
	/**
	 * Creates a new scene
	 * @param		char*						argPName is a custom index name within the scenes collection. 
	 * @return		Scene*
	 */
	Scene* SceneManager::NewScene(char* argPSceneName)
	{
		engine::Logger::Log("Creating Scene", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		Scene* scene = new Scene();
		scenes[argPSceneName] = scene;
		engine::Logger::Log("Scene Created", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		return scene;
	}

	/**
	 * Add a scene to the scene collection within the Scene manager
	 * @param		char*			argPSceneName is the identifier for the scene in the collection
	 * @param		Scene*			Scene is the scene that will be added to the scene collection
	*/
	void SceneManager::AddScene(char* argPSceneName, Scene* argPScene)
	{
		Logger::Log("Adding a custom scene", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		scenes[argPSceneName] = argPScene;
		Logger::Log("Custom scene added", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
	}
	
	Scene* SceneManager::LoadScene(char* argPFileName)
	{
		char line[256];
		Scene* pScene = new Scene();
		std::ifstream inStream (argPFileName);

		if(!inStream.is_open())
		{
			Logger::Log("Scenefile failed to open", Logger::LOG_LEVEL_ERROR, __FILE__, __LINE__);
		}
		else
		{
			Logger::Log("Scenefile opened", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		}

		// Scene name
		Logger::Log("Getting Scenename", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		inStream.getline(line, sizeof(line));
		std::vector<char*> values1 = explode(';', line);
		this->scenes[values1.at(0)] = pScene;

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
		Logger::Log("Scenefile loaded:", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		Logger::Log(argPFileName, Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		return pScene;
	}

	/**
	 * Remove a Scene pointer from the scenes collection.
	 * @param		Scene*						The index name to remove from the collection of scenes.
	 * @return		void
	 */
	void SceneManager::RemoveScene(char* argPSceneName)
	{
		engine::Logger::Log("Removing Scene", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		this -> scenes.erase(argPSceneName);
	}
}
