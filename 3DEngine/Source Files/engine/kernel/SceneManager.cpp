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
		Logger::Log("SceneManager: Initializing", Logger::INFO, __FILE__, __LINE__);

		this->scenes = std::map<std::string, Scene*>();

		Logger::Log("SceneManager: Finished", Logger::INFO, __FILE__, __LINE__);
	}

	/**
	 * Destructs the SceneManager object.
	 * @return		void
	 */
	SceneManager::~SceneManager()
	{
		Logger::Log("SceneManager: Disposing", Logger::INFO, __FILE__, __LINE__);
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void SceneManager::CleanUp()
	{
		std::map<std::string, Scene*>::iterator itScenes;
		for(itScenes = this->scenes.begin(); itScenes != this->scenes.end(); itScenes++)
		{
			delete itScenes->second;
		}
		this->scenes.clear();
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
	 * Loads a scene file and parses it acording to a format:
	 * #resources
	 * <resource type>;<filename>
	 * - resource type can be: "texture" or "model"
	 * - filename is used to indentify a resource.
	 * 
	 * #heigtmap
	 * <heightmap file>;<number of smoothing iterations>;<texture1>;<texture2>;<..texture[n]>
	 * - heightmap has to be an 8bit bmp file
	 * - at the moment only 1 texture works
	 * - the texture has to be loaded in the resource segment
	 *
	 * #camera
	 * <posX>;<posY>;<posZ>;<rotX>;<rotY>;<rotZ>;<scaleX>;<scaleY>;<scaleZ>
	 * - just simple numbers :)
	 *
	 * #models
	 * <modelID>;<posX>;<posY>;<posZ>;<rotX>;<rotY>;<rotZ>;<scaleX>;<scaleY>;<scaleZ>;<modelfile>;<texture1>;<texture2>;<..texture[n]>
	 * - model ID is used to identify it later. this must be unique
	 * - modelfile has to be loaded in the resource segment
	 * - textures has to be loaded in the resouce segment
	 *
	 * #scripts
	 * <ID>;<script1>;<script2>;<..script[n]>
	 * - ID is either "camera" to apply to the camera, a modelID to apply to that model, or empty (start the line with ;) to be applied to the scene
	 * - script can either be a function or a basic mutation of the pos, rot and scale vector; Example: camera;position.x++
	 * 
	 * In addition to this format, lines can also be ignored by prepending an exclamation mark (!) to the line.
	 *
	 * @param		Renderer*		The renderer to use for loading
	 * @param		std::string		The name to store the scene file under
	 * @param		std::string		The scene file to load
	 * @return		Scene*			The created scene
	 */
	Scene* SceneManager::LoadScene(ResourceManager* argPResourceManager, InputManager* argPInputManager,
			Renderer* argPRenderer, std::string argSceneName, std::string argSceneFileName)
	{
		Logger::Log("SceneManager: Loading: " + argSceneFileName, Logger::INFO, __FILE__, __LINE__);
		
		// Create a new scene object to load the data of the scenefile in
		Scene* pScene = new Scene();
		this->scenes[argSceneName] = pScene;
		
		// Parse the correct file name
		std::string fileName = std::string("Resource Files\\Scenes\\" + argSceneFileName);
		// Check if the texture exists
		if (!fileExists(fileName))
		{
			Logger::Log("SceneManager: Scenefile not found: " + fileName, Logger::FATAL, __FILE__, __LINE__);
			return NULL;
		}

		// Create an input stream on the scene file so we can read from it
		std::ifstream inStream (fileName);
		// Check if the scene file has opened
		if(!inStream.is_open())
		{
			Logger::Log("SceneManager: Scenefile failed to open: " + fileName, Logger::FATAL, __FILE__, __LINE__);
		}
		
		// --- Read the scene file
		
		std::string dataCamera;
		std::vector<std::string> dataResources	= std::vector<std::string>();
		std::string dataSkybox;
		std::string dataHeightmap;
		std::vector<std::string> dataModels		= std::vector<std::string>();
		std::string dataInput;
		std::vector<std::string> dataScripts	= std::vector<std::string>();


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
				Logger::Log("SceneManager: +++ Segment - " + curSegment, Logger::INFO, __FILE__, __LINE__);

				// auto set the next line as the line so that we can handle it
				peek = inStream.peek();
				inStream.getline(cLine, sizeof(cLine));
				line = std::string(cLine);
			}

			// Skip empty lines and comment lines (without continue ..)
			if(line.size() > 0 && peek != '!')
			{
				if(curSegment == "camera")
				{
					dataCamera = line;
				}
				else if(curSegment == "resources")
				{
					dataResources.push_back(line);
				}
				else if(curSegment == "skybox")
				{
					dataSkybox = line;
				}
				else if(curSegment == "heightmap")
				{
					dataHeightmap = line;
				}
				else if(curSegment == "models")
				{
					dataModels.push_back(line);
				}
				else if(curSegment == "input")
				{
					dataInput = line;
				}
				else if(curSegment == "scripts")
				{
					dataScripts.push_back(line);
				}
			}
		}
		// Porperly close the scene file
		inStream.close();

		// --- Parse the scene data

		std::vector<std::string> data;


		// === SEGMENT: Camera ===

		// Check if we have camera data, else set it to default
		Logger::Log("SceneManager: Parse camera data", Logger::INFO, __FILE__, __LINE__);
		if(dataCamera.empty())
		{
			Logger::Log("SceneManager: No camera data, loading defaults", Logger::WARNING, __FILE__, __LINE__);
			dataCamera = "0.0;0.0;0.0;0.0;0.0;0.0;1.0;1.0;1.0";
		}
		// Explode the camera data
		data = explode(';', dataCamera);
		
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


		// === SEGMENT: Resources ===

		// Check if we have any resources, give an error we we can't find any
		Logger::Log("SceneManager: Parse resource data", Logger::INFO, __FILE__, __LINE__);
		if(dataResources.empty())
		{
			Logger::Log("SceneManager: No resource data", Logger::FATAL, __FILE__, __LINE__);
		}

		// Loop through the resources
		for each(std::string dataLineResource in dataResources)
		{
			// explode the resource data
			data = explode(';', dataLineResource);

			std::string resourceType		= data.at(0);
			std::string resourceFileName	= data.at(1);

			if(resourceType == "model")
			{
				Logger::Log("SceneManager: Model: " + resourceFileName, Logger::INFO, __FILE__, __LINE__);
				argPResourceManager->LoadMesh(argPRenderer, resourceFileName);
			}
			else if(resourceType == "texture")
			{
				Logger::Log("SceneManager: Texture: " + resourceFileName, Logger::INFO, __FILE__, __LINE__);
				argPResourceManager->LoadTexture(argPRenderer, resourceFileName);
			}
			else
			{
				Logger::Log("SceneManager: Unsupported resource: " + resourceType, Logger::WARNING, __FILE__, __LINE__);
			}
		}


		// === SEGMENT: Skybox ===

		Logger::Log("SceneManager: Parse skybox data", Logger::INFO, __FILE__, __LINE__);
		if(dataSkybox.empty())
		{
			Logger::Log("SceneManager: No skybox data", Logger::WARNING, __FILE__, __LINE__);
		}
		else
		{
			// Explode the heightmap data
			data = explode(';', dataSkybox);

			std::string skyTexture = data.at(0);

			Skybox* pSkybox = new Skybox();
			pSkybox->SetupVertices(argPRenderer);
			pSkybox->SetTexture(0, argPResourceManager->GetTexture(skyTexture));
			pScene->SetSkybox(pSkybox);
		}


		// === SEGMENT: Heightmap ===

		Logger::Log("SceneManager: Parse heightmap data", Logger::INFO, __FILE__, __LINE__);
		if(dataHeightmap.empty())
		{
			Logger::Log("SceneManager: No heightmap data", Logger::WARNING, __FILE__, __LINE__);
		}
		else
		{
			// Explode the heightmap data
			data = explode(';', dataHeightmap);

			std::string mapFileName				= data.at(0);
			unsigned long smoothingIterations	= (unsigned long)std::atof(data.at(1).c_str());

			Heightmap* pHeightmap = new Heightmap();
			pScene->SetHeightmap(pHeightmap);
			pHeightmap->LoadMap(mapFileName);
			pHeightmap->SetupVertices(argPRenderer, smoothingIterations);

			for(unsigned long i = 2; i < data.size(); i++)
			{
				pHeightmap->SetTexture((i - 2), argPResourceManager->GetTexture(data.at(i)));
			}
		}


		// === SEGMENT: Models ===

		Logger::Log("SceneManager: Parse model data", Logger::INFO, __FILE__, __LINE__);
		if(dataModels.empty())
		{
			Logger::Log("SceneManager: No model data", Logger::INFO, __FILE__, __LINE__);
		}

		// Loop through the models
		for each(std::string dataLineModel in dataModels)
		{
			// explode the script data
			data = explode(';', dataLineModel);

			std::string modelName		= data.at(0);
			std::string modelResource	= data.at(10);
			
			Logger::Log("SceneManager: Creating model: " + modelName, Logger::INFO, __FILE__, __LINE__);

			Vector3 position			= Vector3(	(float)std::atof(data.at(1).c_str()),
													(float)std::atof(data.at(2).c_str()),
													(float)std::atof(data.at(3).c_str()));
			Vector3 rotation			= Vector3(	(float)std::atof(data.at(4).c_str()),
													(float)std::atof(data.at(5).c_str()),
													(float)std::atof(data.at(6).c_str()));
			Vector3 scaling				= Vector3(	(float)std::atof(data.at(7).c_str()),
													(float)std::atof(data.at(8).c_str()),
													(float)std::atof(data.at(9).c_str()));

			Model* pModel = new Model(argPResourceManager->NewResource(modelResource));
			pModel->SetPosition(position);
			pModel->SetRotation(rotation);
			pModel->SetScaling(scaling);

			for(unsigned long i = 11; i < data.size(); i++)
			{
				pModel->SetTexture((i - 11), argPResourceManager->GetTexture(data.at(i)));
			}
			pScene->AddModel(modelName, pModel);
		}


		// === SEGMENT: Input ===

		Logger::Log("SceneManager: Parse input data", Logger::INFO, __FILE__, __LINE__);
		if(dataInput.empty())
		{
			Logger::Log("SceneManager: No input data", Logger::INFO, __FILE__, __LINE__);
		}
		else
		{
			// explode the resource data
			data = explode(';', dataInput);

			std::string inputEntity		= data.at(0);
			Logger::Log("SceneManager: Hooking input to: " + inputEntity, Logger::INFO, __FILE__, __LINE__);
			argPInputManager->AddObserver(pScene->GetModel(inputEntity));
		}


		// === SEGMENT: Scripts ===

		Logger::Log("SceneManager: Parse script data", Logger::INFO, __FILE__, __LINE__);
		if(dataScripts.empty())
		{
			Logger::Log("SceneManager: No script data", Logger::INFO, __FILE__, __LINE__);
		}

		// Loop through the scripts
		for each(std::string dataLineScript in dataScripts)
		{
			// explode the script data
			data = explode(';', dataLineScript);

			std::string modelName = data.at(0);

			for(unsigned long i = 1; i < data.size(); i++)
			{
				if(modelName.empty())
				{
					Logger::Log("SceneManager: Adding script to scene", Logger::INFO, __FILE__, __LINE__);
					pScene->AddScript(data.at(i));
				}
				else if(modelName == "camera")
				{
					Logger::Log("SceneManager: Adding script to camera", Logger::INFO, __FILE__, __LINE__);
					pScene->GetCamera()->AddScript(data.at(i));
				}
				else
				{
					Logger::Log("SceneManager: Adding script to model: " + modelName, Logger::INFO, __FILE__, __LINE__);
					pScene->GetModel(modelName)->AddScript(data.at(i));
				}
			}
		}

		Logger::Log("SceneManager: Scenefile: " + argSceneFileName + " loaded", Logger::INFO, __FILE__, __LINE__);
		return pScene;
	}

	/**
	 * Remove a Scene pointer from the scenes collection.
	 * @param		std::string					The index name to remove from the collection of scenes.
	 * @return		void
	 */
	void SceneManager::RemoveScene(std::string argSceneName)
	{
		this -> scenes.erase(argSceneName);
	}
}
