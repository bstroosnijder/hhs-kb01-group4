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
	 * Creates a new empty scene
	 * @param		std::string		The identifier of the scene
	 * @return		Scene*
	 */
	Scene* SceneManager::NewScene(std::string argPSceneName)
	{
		Scene* pScene = new Scene();
		this->scenes[argPSceneName] = pScene;
		return pScene;
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
		
		Scene* pScene;
		// Check if the scene already exists
		if(this->scenes.count(argSceneName)  == 1)
		{
			pScene = this->scenes[argSceneName];
		}
		// Create a new scene if it doesn't
		else
		{
			pScene = new Scene();
			this->scenes[argSceneName] = pScene;
		}
		
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
		std::vector<std::string> dataEntities	= std::vector<std::string>();
		std::vector<std::string> dataLights		= std::vector<std::string>();
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
				else if(curSegment == "entities")
				{
					dataEntities.push_back(line);
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

			std::string skyTexture	= data.at(0);
			unsigned long skySize	= (unsigned long)std::atof(data.at(1).c_str());
			argPResourceManager->LoadTexture(argPRenderer, skyTexture);

			Skybox* pSkybox = new Skybox();
			pSkybox->SetupVertices(argPRenderer, skySize);
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
			float pixelScale					= (float)std::atof(data.at(1).c_str());
			unsigned long smoothingIterations	= (unsigned long)std::atof(data.at(2).c_str());

			Heightmap* pHeightmap = new Heightmap();
			pScene->SetHeightmap(pHeightmap);
			pHeightmap->SetupVertices(argPRenderer, mapFileName, pixelScale, smoothingIterations);

			for(unsigned long i = 3; i < data.size(); i++)
			{
				std::string mapTexture = data.at(i);
				argPResourceManager->LoadTexture(argPRenderer, mapTexture);

				pHeightmap->SetTexture((i - 3), argPResourceManager->GetTexture(mapTexture));
			}
		}


		// === SEGMENT: Entities ===
		Logger::Log("\nSceneManager: +++ Segment - Entities", Logger::INFO, __FILE__, __LINE__);

		if(dataEntities.empty())
		{
			Logger::Log("SceneManager: No entity data", Logger::INFO, __FILE__, __LINE__);
		}

		std::vector<Entity*> entityStack	= std::vector<Entity*>();
		int numPrevTabs = 0;
		// Loop through the entities
		std::vector<std::string>::iterator entityIt;
		for(entityIt = dataEntities.begin(); entityIt != dataEntities.end(); entityIt++)
		{
			std::string dataLineEntity		= *entityIt;
			// explode the entity data
			data = explode(';', dataLineEntity);

			std::string entityName			= data.at(0);
			std::string entityType			= data.at(1);

			int numTabs						= std::count(entityName.begin(), entityName.end(), '\t');
			// Remove the tabs from the entity name
			entityName						= entityName.substr(numTabs);
			if(!entityStack.empty() && numTabs <= numPrevTabs)
			{
				for(long i = 0; i <= (numPrevTabs - numTabs); i++)
				{
					entityStack.pop_back();
				}
			}

			// The entity
			Entity* pEntity;
			// The properties of the entity
			Vector3 position;
			Vector3 rotation;
			Vector3 scaling;

			if(entityType == "model")
			{
				Logger::Log("SceneManager: Creating model: " + entityName, Logger::INFO, __FILE__, __LINE__);

				std::string modelMesh	= data.at(11);
				argPResourceManager->LoadMesh(argPRenderer, modelMesh);

				position			= Vector3(	(float)std::atof(data.at(2).c_str()),
												(float)std::atof(data.at(3).c_str()),
												(float)std::atof(data.at(4).c_str()));
				rotation			= Vector3(	(float)std::atof(data.at(5).c_str()),
												(float)std::atof(data.at(6).c_str()),
												(float)std::atof(data.at(7).c_str()));
				scaling				= Vector3(	(float)std::atof(data.at(8).c_str()),
												(float)std::atof(data.at(9).c_str()),
												(float)std::atof(data.at(10).c_str()));
				
				// Create the model
				pEntity				= new Model(argPResourceManager->NewResource(modelMesh));
				unsigned long iTex	= 12;
				for(unsigned long i = iTex; i < data.size(); i++)
				{
					std::string modelTexture = data.at(i);
					argPResourceManager->LoadTexture(argPRenderer, modelTexture);

					((Model*)pEntity)->SetTexture((i - iTex), argPResourceManager->GetTexture(modelTexture));
				}

			}
			else if(entityType == "light")
			{
				Logger::Log("SceneManager: Creating light: " + entityName, Logger::INFO, __FILE__, __LINE__);

				position			= Vector3(	(float)std::atof(data.at(2).c_str()),
												(float)std::atof(data.at(3).c_str()),
												(float)std::atof(data.at(4).c_str()));
				rotation			= Vector3(0.0f, 0.0f, 0.0f);
				scaling				= Vector3(1.0f, 1.0f, 1.0f);
				float lightRange	= (float)std::atof(data.at(5).c_str());
				float colorR		= (float)std::atof(data.at(6).c_str());
				float colorG		= (float)std::atof(data.at(7).c_str());
				float colorB		= (float)std::atof(data.at(8).c_str());
				float colorA		= (float)std::atof(data.at(9).c_str());
				
				// Create the lightpoint
				pEntity				= new LightPoint(argPRenderer->GetNextLightIndex());
				((LightPoint*)pEntity)->SetRange(lightRange);
				((LightPoint*)pEntity)->SetColor(colorR, colorG, colorB, colorA);
			}
			else
			{
				Logger::Log("SceneManager: Unsupported entity type: " + entityType, Logger::WARNING, __FILE__, __LINE__);
			}

			// Set entity properties
			pEntity->SetPosition(position);
			pEntity->SetRotation(rotation);
			pEntity->SetScaling(scaling);

			// Add entity to the last entity in the stack
			if(!entityStack.empty() && numTabs > 0)
			{
				entityStack.back()->AddEntity(entityName, pEntity);
			}
			// Add entity to the scene
			else
			{
				pScene->AddEntity(entityName, pEntity);
			}

			// Add the new entity to the stack
			entityStack.push_back(pEntity);
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

			if(action == "option")
			{
				std::string key		= data.at(2);
				std::string value	= data.at(3);

				Logger::Log("SceneManager: Adding device option " + device + "." + key + " = " + value, Logger::INFO, __FILE__, __LINE__);
				if(device == "keyboard" && argPInputManager->HasDevice(InputManager::KEYBOARD))
				{
					argPInputManager->GetKeyboard()->SetOption(key, value);
				}
				else if(device == "mouse" && argPInputManager->HasDevice(InputManager::MOUSE))
				{
					argPInputManager->GetMouse()->SetOption(key, value);
				}
				else if(device == "joystick" && argPInputManager->HasDevice(InputManager::JOYSTICK))
				{
					argPInputManager->GetJoyStick()->SetOption(key, value);
				}
			}
			// Hook an entity to an input device
			else if(action == "hook")
			{
				std::string entity = data.at(2);

				InputListener* pInputListener;
				if(entity == "camera")
				{
					pInputListener = pScene->GetCamera();
				}
				else if(entity == "renderer")
				{
					DirectX9Renderer* pRenderer = (DirectX9Renderer*)argPRenderer;
					pInputListener = (InputListener*) pRenderer;
				}
				else
				{
					pInputListener = pScene->GetEntity(entity);
				}


				if(device == "keyboard" && argPInputManager->HasDevice(InputManager::KEYBOARD))
				{
					argPInputManager->GetKeyboard()->AddInputListener(pInputListener);
				}
				else if(device == "mouse" && argPInputManager->HasDevice(InputManager::MOUSE))
				{
					argPInputManager->GetMouse()->AddInputListener(pInputListener);
				}
				else if(device == "joystick" && argPInputManager->HasDevice(InputManager::JOYSTICK))
				{
					argPInputManager->GetJoyStick()->AddInputListener(pInputListener);
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
			std::string dataLineScript	= dataScripts[lineIndex];
			// explode the script data
			data						= explode(';', dataLineScript);
			std::string entityName		= data.at(0);

			for(unsigned long i = 1; i < data.size(); i++)
			{
				if(entityName.empty())
				{
					Logger::Log("SceneManager: Adding script to scene", Logger::INFO, __FILE__, __LINE__);
					pScene->AddScript(data.at(i));
				}
				else if(entityName == "camera")
				{
					Logger::Log("SceneManager: Adding script to camera", Logger::INFO, __FILE__, __LINE__);
					pScene->GetCamera()->AddScript(data.at(i));
				}
				else
				{
					Logger::Log("SceneManager: Adding script to entity: " + entityName, Logger::INFO, __FILE__, __LINE__);
					std::vector<std::string> entityNameParts	= explode(':', entityName);

					Entity* pEntity								= pScene->GetEntity(entityNameParts.front());
					for(unsigned long j = 1; j < entityNameParts.size(); j++)
					{
						pEntity = pEntity->GetEntity(entityNameParts.at(j));
					}

					pEntity->AddScript(data.at(i));
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
