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
	 * #heightmap
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
		std::string dataSkybox;
		std::string dataHeightmap;
		std::vector<std::string> dataModels		= std::vector<std::string>();
		std::vector<std::string> dataInput		= std::vector<std::string>();
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
					dataInput.push_back(line);
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
		Logger::Log("\nSceneManager: +++ Segment - Camera", Logger::INFO, __FILE__, __LINE__);

		// Check if we have camera data, else set it to default
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


		// === SEGMENT: Skybox ===
		Logger::Log("\nSceneManager: +++ Segment - Skybox", Logger::INFO, __FILE__, __LINE__);

		if(dataSkybox.empty())
		{
			Logger::Log("SceneManager: No skybox data", Logger::WARNING, __FILE__, __LINE__);
		}
		else
		{
			// Explode the heightmap data
			data = explode(';', dataSkybox);

			std::string skyTexture = data.at(0);
			argPResourceManager->LoadTexture(argPRenderer, skyTexture);

			Skybox* pSkybox = new Skybox();
			pSkybox->SetupVertices(argPRenderer);
			pSkybox->SetTexture(0, argPResourceManager->GetTexture(skyTexture));
			pScene->SetSkybox(pSkybox);
		}


		// === SEGMENT: Heightmap ===
		Logger::Log("\nSceneManager: +++ Segment - Heightmap", Logger::INFO, __FILE__, __LINE__);

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
				std::string mapTexture = data.at(i);
				argPResourceManager->LoadTexture(argPRenderer, mapTexture);

				pHeightmap->SetTexture((i - 2), argPResourceManager->GetTexture(mapTexture));
			}
		}


		// === SEGMENT: Models ===
		Logger::Log("\nSceneManager: +++ Segment - Models", Logger::INFO, __FILE__, __LINE__);

		if(dataModels.empty())
		{
			Logger::Log("SceneManager: No model data", Logger::INFO, __FILE__, __LINE__);
		}

		std::vector<Model*> modelStack = std::vector<Model*>();
		int numPrevTabs = 0;
		// Loop through the models
		std::vector<std::string>::iterator modelIt;
		for(modelIt = dataModels.begin(); modelIt != dataModels.end(); modelIt++)
		{
			std::string dataLineModel = *modelIt;
			// explode the resource data
			data = explode(';', dataLineModel);

			std::string modelName		= data.at(0);
			std::string modelResource	= data.at(10);
			argPResourceManager->LoadMesh(argPRenderer, modelResource);

			int numTabs					= std::count(modelName.begin(), modelName.end(), '\t');
			// Remove the tabs from the model name
			modelName = modelName.substr(numTabs);
			if(!modelStack.empty() && numTabs <= numPrevTabs)
			{
				for(long i = 0; i <= (numPrevTabs - numTabs); i++)
				{
					modelStack.pop_back();
				}
			}

			
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
				std::string modelTexture = data.at(i);
				argPResourceManager->LoadTexture(argPRenderer, modelTexture);

				pModel->SetTexture((i - 11), argPResourceManager->GetTexture(modelTexture));
			}

			if(!modelStack.empty() && numTabs > 0)
			{
				modelStack.back()->AddModel(modelName, pModel);
			}
			else
			{
				pScene->AddModel(modelName, pModel);
			}

			modelStack.push_back(pModel);

			// Set the number of prev tabs for the next iteration
			numPrevTabs = numTabs;
		}


		// === SEGMENT: Input ===
		Logger::Log("\nSceneManager: +++ Segment - Input", Logger::INFO, __FILE__, __LINE__);

		if(dataInput.empty())
		{
			Logger::Log("SceneManager: No input data", Logger::INFO, __FILE__, __LINE__);
		}

		// Loop through the input data
		std::vector<std::string>::iterator inputIt;
		for(inputIt = dataInput.begin(); inputIt != dataInput.end(); inputIt++)
		{
			std::string dataLineInput = *inputIt;
			// explode the resource data
			data = explode(';', dataLineInput);

			std::string action	= data.at(0);
			std::string device	= data.at(1);

			// Hook an entity to an input device
			if(action == "hook")
			{
				std::string entity = data.at(2);
				if(device == "keyboard" && argPInputManager->HasDevice(InputManager::KEYBOARD))
				{
					if(entity == "camera")
					{
						argPInputManager->GetKeyboard()->AddListener(pScene->GetCamera());
					}
					else
					{
						argPInputManager->GetKeyboard()->AddListener(pScene->GetModel(entity));
					}
				}
				else if(device == "mouse" && argPInputManager->HasDevice(InputManager::MOUSE))
				{
					if(entity == "camera")
					{
						argPInputManager->GetMouse()->AddListener(pScene->GetCamera());
					}
					else
					{
						argPInputManager->GetMouse()->AddListener(pScene->GetModel(entity));
					}
				}
				else if(device == "joystick" && argPInputManager->HasDevice(InputManager::JOYSTICK))
				{
					if(entity == "camera")
					{
						argPInputManager->GetJoyStick()->AddListener(pScene->GetCamera());
					}
					else
					{
						argPInputManager->GetJoyStick()->AddListener(pScene->GetModel(entity));
					}
				}
				else
				{
					Logger::Log("Could not hook input to device: " + device, Logger::WARNING, __FILE__, __LINE__);
				}
			}
			// Map binds to keys of a device
			else if(action == "bind")
			{
				std::string bind = data.at(2);
				for(unsigned long i = 3; i < data.size(); i++)
				{
					std::string key = data.at(i);
					Logger::Log("SceneManager: " + key + ": " + bind, Logger::INFO, __FILE__, __LINE__);

					InputDevice* pInputDevice = NULL;
					if(device == "keyboard" && argPInputManager->HasDevice(InputManager::KEYBOARD))
					{
						pInputDevice = argPInputManager->GetDevice(InputManager::KEYBOARD);
					}
					else if(device == "mouse" && argPInputManager->HasDevice(InputManager::MOUSE))
					{
						pInputDevice = argPInputManager->GetDevice(InputManager::MOUSE);
					}

					else if(device == "joystick" && argPInputManager->HasDevice(InputManager::JOYSTICK))
					{
						pInputDevice = argPInputManager->GetDevice(InputManager::JOYSTICK);
					}

					if(pInputDevice != NULL)
					{
						pInputDevice->AddBind(key, bind);
					}
				}
			}
		}


		// === SEGMENT: Scripts ===
		Logger::Log("\nSceneManager: +++ Segment - Scripts", Logger::INFO, __FILE__, __LINE__);

		if(dataScripts.empty())
		{
			Logger::Log("SceneManager: No script data", Logger::INFO, __FILE__, __LINE__);
		}

		// Loop through the scripts
		for(unsigned int lineIndex = 0; lineIndex < dataScripts.size(); lineIndex++)
		{
			std::string dataLineScript = dataScripts[lineIndex];
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
					std::vector<std::string> modelNameParts = explode(':', modelName);

					Model* pModel = pScene->GetModel(modelNameParts.front());
					for(unsigned long j = 1; j < modelNameParts.size(); j++)
					{
						pModel = pModel->GetModel(modelNameParts.at(j));
					}

					pModel->AddScript(data.at(i));
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
