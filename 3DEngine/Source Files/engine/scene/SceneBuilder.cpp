#include "..\..\..\Header Files\engine\scene\SceneBuilder.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	
	/**
	 * Checks if the value is a float. If it is, return it. Otherwise return the default
	 * @param		std::string		The value to check
	 * @param		float			The default value
	 * @return		float
	 */
	float SceneBuilder::FloatIfStringDefault(std::string argValue, float argDefault)
	{
		float data;

		if(argValue == "d")
		{
			data = argDefault;
		}
		else
		{
			data = (float)std::atof(argValue.c_str());
		}

		return data;
	}

	//---Public methods---

	/**
	 * Constructs the SceneBuilder object
	 */
	SceneBuilder::SceneBuilder(std::string argFileName, Scene* argPScene,
						ResourceManager* argPResourceManager, Renderer* argPRenderer)
	{
		Logger::Log("SceneBuilder: Initializing", Logger::INFO, __FILE__, __LINE__);

		this->fileName			= argFileName;
		this->pScene			= argPScene;
		this->pResourceManager	= argPResourceManager;
		this->pRenderer			= argPRenderer;

		this->modelMesh			= std::map<std::string, std::string>();
		this->modelTextures		= std::map<std::string, std::map<unsigned long, std::string>>();
		this->soundWavFile		= std::map<std::string, std::string>();

		Logger::Log("SceneBuilder: Finished", Logger::INFO, __FILE__, __LINE__);
	}

	/**
	 * Destructs the Scene object.
	 */
	SceneBuilder::~SceneBuilder()
	{
		Logger::Log("SceneBuilder: Disposing", Logger::INFO, __FILE__, __LINE__);
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing this object.
	 * @return		void
	 */
	void SceneBuilder::CleanUp()
	{
	}

	/**
	 * Processes any input events
	 * @param		std::string		the bind to execute
	 * @param		float			the speed
	 * @return		void
	 */
	void SceneBuilder::InputEvent(std::string argBind, float argSpeed)
	{
		if(argBind == "spawn")
		{
			// buffer and data storage
			std::string buffer;
			std::vector<std::string> data;

			std::string eName;
			Logger::Log("SceneBuilder: What is the entity ID? (has to be unique)", Logger::INFO, __FILE__, __LINE__);
			std::cin >> eName;

			std::string eType;
			Logger::Log("SceneBuilder: What type of entity is it? (model, light, sound)", Logger::INFO, __FILE__, __LINE__);
			std::cin >> eType;

			Vector3 pos;
			Logger::Log("SceneBuilder: What is the position vector? (x;y;z) | (camera) | (center)", Logger::INFO, __FILE__, __LINE__);
			std::cin >> buffer;

			if(buffer == "camera")
			{
				pos = this->pScene->GetCamera()->GetPosition();
			}
			else if(buffer == "center")
			{
				pos = Vector3(0.0f, 0.0f, 0.0f);
			}
			else
			{
				data = explode(';', buffer);
				pos.x = (float)std::atof(data.at(0).c_str());
				pos.y = (float)std::atof(data.at(1).c_str());
				pos.z = (float)std::atof(data.at(2).c_str());
			}

			Entity* pEntity;
			if(eType == "model")
			{
				Logger::Log("SceneBuilder: Creating new model", Logger::INFO, __FILE__, __LINE__);

				std::string fileName;
				Logger::Log("SceneBuilder: Where is the mesh file located? (searching in dir 'Resource Files/Models/')", Logger::INFO, __FILE__, __LINE__);
				std::cin >> fileName;

				this->modelMesh[eName] = fileName;
				this->pResourceManager->LoadMesh(this->pRenderer, fileName);
				pEntity = new Model(this->pResourceManager->NewResource(fileName));

				Vector3 rot;
				Logger::Log("SceneBuilder: What is the rotation vector? (x;y;z) | (camera) | (center)", Logger::INFO, __FILE__, __LINE__);
				std::cin >> buffer;

				if(buffer == "camera")
				{
					rot = this->pScene->GetCamera()->GetRotation();
				}
				else if(buffer == "center")
				{
					rot = Vector3(0.0f, 0.0f, 0.0f);
				}
				else
				{
					data = explode(';', buffer);
					rot.x = (float)std::atof(data.at(0).c_str());
					rot.y = (float)std::atof(data.at(1).c_str());
					rot.z = (float)std::atof(data.at(2).c_str());
				}
				pEntity->SetRotation(rot);

				Vector3 scale;
				Logger::Log("SceneBuilder: What is the scale vector? (x;y;z) | (camera) | (center)", Logger::INFO, __FILE__, __LINE__);
				std::cin >> buffer;

				if(buffer == "camera")
				{
					scale = this->pScene->GetCamera()->GetRotation();
				}
				else if(buffer == "center")
				{
					scale = Vector3(1.0f, 1.0f, 1.0f);
				}
				else
				{
					data = explode(';', buffer);
					scale.x = (float)std::atof(data.at(0).c_str());
					scale.y = (float)std::atof(data.at(1).c_str());
					scale.z = (float)std::atof(data.at(2).c_str());
				}
				pEntity->SetRotation(rot);

				do
				{
					Logger::Log("SceneBuilder: Load custom texture? (i;filename) d = done", Logger::INFO, __FILE__, __LINE__);
					std::cin >> buffer;

					if(!buffer.empty() && buffer != "d")
					{
						data = explode(';', buffer);
						unsigned long texIndex	= (unsigned long)std::atol(data.at(0).c_str());
						std::string texFileName	= data.at(1);

						this->modelTextures[eName][texIndex] = texFileName;
						this->pResourceManager->LoadTexture(this->pRenderer, texFileName);
						((Model*)pEntity)->SetTexture(texIndex, this->pResourceManager->GetTexture(texFileName));
					}
				}
				while(!buffer.empty() && buffer != "d");


			}
			else if(eType == "light")
			{
				Logger::Log("SceneBuilder: Creating new light", Logger::INFO, __FILE__, __LINE__);
				pEntity = new LightPoint(this->pRenderer->GetNextLightIndex());

				Logger::Log("SceneBuilder: What is the radius of the light entity?", Logger::INFO, __FILE__, __LINE__);
				std::cin >> buffer;
				((LightPoint*)pEntity)->SetRange((float)std::atof(buffer.c_str()));

				Logger::Log("SceneBuilder: What is the color of the light entity? (r;g;b;a)", Logger::INFO, __FILE__, __LINE__);
				std::cin >> buffer;
				data = explode(';', buffer);
				((LightPoint*)pEntity)->SetColor(	(float)std::atof(data.at(0).c_str()),
													(float)std::atof(data.at(1).c_str()),
													(float)std::atof(data.at(2).c_str()),
													(float)std::atof(data.at(3).c_str()));

			}
			else if(eType == "sound")
			{
				Logger::Log("SceneBuilder: Creating new sound", Logger::INFO, __FILE__, __LINE__);

				std::string fileName;
				Logger::Log("SceneBuilder: Where is the wave file located? (searching in dir 'Resource Files/Sounds/')", Logger::INFO, __FILE__, __LINE__);
				std::cin >> fileName;

				this->soundWavFile[eName] = fileName;
				this->pResourceManager->LoadWav(fileName);
				pEntity = new Sound(this->pResourceManager->GetWav(fileName));
			}
			else
			{
				Logger::Log("SceneBuilder: The type " + eType + " is not supported", Logger::WARNING, __FILE__, __LINE__);
				return;
			}
			
			pEntity->SetPosition(pos);
			Logger::Log("SceneBuilder: Adding entity to scene", Logger::INFO, __FILE__, __LINE__);
			this->pScene->AddEntity(eName, pEntity);
		}
		else if(argBind == "load")
		{
			// buffer and data storage
			std::string buffer;
			std::vector<std::string> data;

			std::string type;
			Logger::Log("SceneBuilder: What do you want to load? skybox/heightmap", Logger::INFO, __FILE__, __LINE__);
			std::cin >> type;

			if(type == "skybox")
			{
				Logger::Log("SceneBuilder: Creating new skybox", Logger::INFO, __FILE__, __LINE__);
				Skybox* pSkybox = new Skybox();

				Logger::Log("SceneBuilder: How large should the skybox be?", Logger::INFO, __FILE__, __LINE__);
				std::cin >> buffer;
				pSkybox->SetupVertices(this->pRenderer, (unsigned long)std::atol(buffer.c_str()));

				std::string fileName;
				Logger::Log("SceneBuilder: Where is the texture file located? (searching in dir 'Resource Files/Textures/')", Logger::INFO, __FILE__, __LINE__);
				std::cin >> fileName;

				this->skyboxTexture = fileName;
				this->pResourceManager->LoadTexture(this->pRenderer, fileName);
				pSkybox->SetTexture(0, this->pResourceManager->GetTexture(fileName));
				
				Logger::Log("SceneBuilder: Adding skybox to scene", Logger::INFO, __FILE__, __LINE__);
				this->pScene->SetSkybox(pSkybox);
			}
			else if(type == "heightmap")
			{
				Logger::Log("SceneBuilder: Creating new heightmap", Logger::INFO, __FILE__, __LINE__);
				Heightmap* pHeightmap = new Heightmap();

				std::string bitmapFileName;
				Logger::Log("SceneBuilder: Where is the bitmap located? (searching in dir 'Resource Files/Textures/')", Logger::INFO, __FILE__, __LINE__);
				std::cin >> bitmapFileName;

				float pixelScale;
				Logger::Log("SceneBuilder: How large should each pixel be scaled?", Logger::INFO, __FILE__, __LINE__);
				std::cin >> buffer;
				pixelScale = (float)std::atof(buffer.c_str());

				unsigned long smoothing;
				Logger::Log("SceneBuilder: How smooth should the heightmap be?", Logger::INFO, __FILE__, __LINE__);
				std::cin >> buffer;
				smoothing = (unsigned long)std::atol(buffer.c_str());

				std::string textureFileName;
				Logger::Log("SceneBuilder: Where is the texture located? (searching in dir 'Resource Files/Textures/')", Logger::INFO, __FILE__, __LINE__);
				std::cin >> textureFileName;

				this->heightmapBitmap = bitmapFileName;
				this->heightmapTextures[0] = textureFileName;
				pHeightmap->SetupVertices(this->pRenderer, bitmapFileName, pixelScale, smoothing);
				this->pResourceManager->LoadTexture(this->pRenderer, textureFileName);
				pHeightmap->SetTexture(0, this->pResourceManager->GetTexture(textureFileName));
				
				Logger::Log("SceneBuilder: Adding heightmap to scene", Logger::INFO, __FILE__, __LINE__);
				this->pScene->SetHeightmap(pHeightmap);
			}
			else
			{
				Logger::Log("SceneBuilder: The type " + type + " is not supported", Logger::WARNING, __FILE__, __LINE__);
				return;
			}
		}
		else if(argBind == "modify")
		{
			// buffer and data storage
			std::string buffer;
			std::vector<std::string> data;
			
			std::string eName;
			Logger::Log("SceneBuilder: What is the entity ID?", Logger::INFO, __FILE__, __LINE__);
			std::cin >> buffer;
			data = explode(':', buffer);
			eName = data.back();

			Entity* pEntity;
			if(buffer == "camera")
			{
				pEntity = this->pScene->GetCamera();
			}
			else if(data.size() > 1)
			{
				// TODO
			}
			else
			{
				pEntity = this->pScene->GetEntity(data.front());
			}

			std::string action;
			Logger::Log("SceneBuilder: What do you want to do? pos/rot/scale/addscript/addentity", Logger::INFO, __FILE__, __LINE__);
			std::cin >> action;

			if(action == "pos")
			{
				Vector3 pos;
				Logger::Log("SceneBuilder: What is the position vector? (x;y;z) | (camera) | (center)", Logger::INFO, __FILE__, __LINE__);
				std::cin >> buffer;

				if(buffer == "camera")
				{
					pos = this->pScene->GetCamera()->GetPosition();
				}
				else if(buffer == "center")
				{
					pos = Vector3(0.0f, 0.0f, 0.0f);
				}
				else
				{
					data = explode(';', buffer);
					pos.x = (float)std::atof(data.at(0).c_str());
					pos.y = (float)std::atof(data.at(1).c_str());
					pos.z = (float)std::atof(data.at(2).c_str());
				}

				pEntity->SetPosition(pos);
			}
			else if(action == "rot")
			{
				Vector3 rot;
				Logger::Log("SceneBuilder: What is the rotation vector? (x;y;z) | (camera) | (center)", Logger::INFO, __FILE__, __LINE__);
				std::cin >> buffer;

				if(buffer == "camera")
				{
					rot = this->pScene->GetCamera()->GetRotation();
				}
				else if(buffer == "center")
				{
					rot = Vector3(0.0f, 0.0f, 0.0f);
				}
				else
				{
					data = explode(';', buffer);
					rot.x = (float)std::atof(data.at(0).c_str());
					rot.y = (float)std::atof(data.at(1).c_str());
					rot.z = (float)std::atof(data.at(2).c_str());
				}

				pEntity->SetRotation(rot);
			}
			else if(action == "scale")
			{
				Vector3 scale;
				Logger::Log("SceneBuilder: What is the scaling vector? (x;y;z) | (camera) | (center)", Logger::INFO, __FILE__, __LINE__);
				std::cin >> buffer;

				if(buffer == "camera")
				{
					scale = this->pScene->GetCamera()->GetScaling();
				}
				else if(buffer == "center")
				{
					scale = Vector3(0.0f, 0.0f, 0.0f);
				}
				else
				{
					data = explode(';', buffer);
					scale.x = (float)std::atof(data.at(0).c_str());
					scale.y = (float)std::atof(data.at(1).c_str());
					scale.z = (float)std::atof(data.at(2).c_str());
				}

				pEntity->SetScaling(scale);
			}
			else if(action == "addscript")
			{
				std::string script;
				Logger::Log("SceneBuilder: What script to add?", Logger::INFO, __FILE__, __LINE__);
				std::cin >> script;

				pEntity->AddScript(script);
			}
		}
		else if(argBind == "delete")
		{
		}
		else if(argBind == "clear")
		{
			std::string clear = "n";
			Logger::Log("SceneBuilder: Are you sure you want to clear the scene? y/n", Logger::WARNING, __FILE__, __LINE__);
			std::cin >> clear;

			if(clear.empty() && clear == "n")
			{
				Logger::Log("SceneBuilder: Not clearing the scene", Logger::INFO, __FILE__, __LINE__);
				return;
			}

			
			// === Segment: Camera ===
			Camera* pCamera	= this->pScene->GetCamera();
			Logger::Log("SceneBuilder: Clearing camera data", Logger::INFO, __FILE__, __LINE__);
			pCamera->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			pCamera->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			pCamera->SetScaling(Vector3(1.0f, 1.0f, 1.0f));

			// === SEGMENT: Skybox ===
			Logger::Log("SceneBuilder: Clearing skybox data", Logger::INFO, __FILE__, __LINE__);
			pScene->SetSkybox(NULL);

			// === SEGMENT: Heightmap ===
			Logger::Log("SceneBuilder: Clearing heightmap data", Logger::INFO, __FILE__, __LINE__);
			pScene->SetHeightmap(NULL);

			// === SEGMENT: Entities ===
			Logger::Log("SceneBuilder: Writing entity data", Logger::INFO, __FILE__, __LINE__);
			std::map<std::string, Entity*> entities = pScene->GetEntities();
			std::map<std::string, Entity*>::iterator entitiesIt;
			for(entitiesIt = entities.begin(); entitiesIt != entities.end(); entitiesIt++)
			{
				Entity* pEntity = entitiesIt->second;
				delete pEntity;
			}
			entities.clear();

			// === SEGMENT: Scripts ===
			Logger::Log("SceneBuilder: Writing script data", Logger::INFO, __FILE__, __LINE__);
			pScene->GetScripts().clear();
		}
		else if(argBind == "save")
		{
			std::string rDir		= "Resource Files\\Scenes\\";
			// Parse a default file name
			std::string rFileName = rDir + this->fileName + ".scene";

			// Where do we save, lets ask the user
			Logger::Log("SceneBuilder: Give me a file name pl0x!", Logger::INFO, __FILE__, __LINE__);
			std::cin >> rFileName;
			Logger::Log(rFileName, Logger::INFO, __FILE__, __LINE__);
			
			// Does it already exists?
			if(fileExists(rDir + rFileName))
			{
				// Are we allowed to overwrite?
				std::string overwrite = "n";
				Logger::Log("SceneBuilder: The file already exists, overwrite? y/n", Logger::WARNING, __FILE__, __LINE__);
				std::cin >> overwrite;

				if(overwrite.empty() || overwrite == "n")
				{
					Logger::Log("SceneBuilder: Didn't save the file", Logger::INFO, __FILE__, __LINE__);
					return;
				}
			}

			
			// Create the output stream
			std::ofstream out	= std::ofstream(rDir + rFileName);


			// === Segment: Camera ===
			Camera* pCamera	= this->pScene->GetCamera();
			Logger::Log("SceneBuilder: Writing camera data", Logger::INFO, __FILE__, __LINE__);
			out << "#camera" << std::endl;

			Vector3 cPos	= pCamera->GetPosition();
			out << cPos.x << ";" << cPos.y << ";" << cPos.z << ";";

			Vector3 cRot	= pCamera->GetRotation();
			out << cRot.x << ";" << cRot.y << ";" << cRot.z << ";";

			Vector3 cScale	= pCamera->GetScaling();
			out << cScale.x << ";" << cScale.y << ";" << cScale.z << std::endl;

			
			// === SEGMENT: Skybox ===
			Skybox* pSkybox	= this->pScene->GetSkybox();
			if(pSkybox != NULL)
			{
				Logger::Log("SceneBuilder: Writing skybox data", Logger::INFO, __FILE__, __LINE__);
				out << "#skybox" << std::endl;
				
				float skySize			= pSkybox->GetSize();
				out << this->skyboxTexture << ";";
				out << skySize << std::endl;
			}

			
			// === SEGMENT: Heightmap ===
			Heightmap* pHeightmap	= this->pScene->GetHeightmap();
			if(pHeightmap != NULL)
			{
				Logger::Log("SceneBuilder: Writing heightmap data", Logger::INFO, __FILE__, __LINE__);
				out << "#heightmap" << std::endl;
				
				out << this->heightmapBitmap << ";";

				float mapScaling		= pHeightmap->GetScaling();
				out << mapScaling << ";";

				long mapSmoothing		= pHeightmap->GetSmoothing();
				out << mapSmoothing;

				for(unsigned long i = 0; i < 8; i++)
				{
					if(!this->heightmapTextures[i].empty())
					{
						out << ";" << this->heightmapTextures[i];
					}
				}

				out << std::endl;
			}


			// === SEGMENT: Entities ===
			std::map<std::string, Entity*> entities = pScene->GetEntities();
			std::vector<Entity*> entityStack	= std::vector<Entity*>();
			Logger::Log("SceneBuilder: Writing entity data", Logger::INFO, __FILE__, __LINE__);
			out << "#entities" << std::endl;

			std::map<std::string, Entity*>::iterator entitiesIt;
			for(entitiesIt = entities.begin(); entitiesIt != entities.end(); entitiesIt++)
			{
				// Add the entity to the stack
				Entity* pEntity		= entitiesIt->second;
				entityStack.push_back(pEntity);
				
				std::string eName	= entitiesIt->first;
				out << eName << ";";

				if(pEntity->GetType() == Entity::LIGHTPOINT)
				{
					std::string eType	= "light";
					out << eType << ";";

					Vector3 ePos		= pEntity->GetPosition();
					out << ePos.x << ";" << ePos.y << ";" << ePos.z << ";";

					D3DXCOLOR lColor = ((LightPoint*)pEntity)->GetColor();
					out << lColor.r << ";" << lColor.g << ";" << lColor.b << ";" << lColor.a;
				}
				else if(pEntity->GetType() == Entity::SOUND)
				{
					std::string eType	= "sound";
					out << eType << ";";

					Vector3 ePos		= pEntity->GetPosition();
					out << ePos.x << ";" << ePos.y << ";" << ePos.z << ";";

					out << this->soundWavFile[eName];
				}
				// Default save model
				else
				{
					std::string eType	= "model";
					out << eType << ";";

					Vector3 ePos		= pEntity->GetPosition();
					out << ePos.x << ";" << ePos.y << ";" << ePos.z << ";";

					Vector3 eRot		= pEntity->GetRotation();
					out << eRot.x << ";" << eRot.y << ";" << eRot.z << ";";
					
					Vector3 eScale		= pEntity->GetScaling();
					out << eScale.x << ";" << eScale.y << ";" << eScale.z << ";";

					out << this->modelMesh.at(eName);

					std::map<unsigned long, std::string>::iterator texturesIt;
					for(texturesIt = this->modelTextures[eName].begin(); texturesIt != this->modelTextures[eName].end(); texturesIt++)
					{
						unsigned long texIndex	= texturesIt->first;
						std::string texFileName	= texturesIt->second;

						out << ";" << texFileName;
					}
					// TODO: TEXTURES
				}

				out << std::endl;
				// TODO: SUB ENTITIES
				//out << this->WriteSubEntities(pEntity);
			}


			Logger::Log("SceneBuilder: Closing file", Logger::INFO, __FILE__, __LINE__);
			// Save the scene file
			out.close();
		}
	}

	/**
	 * Saves the scene to the disk
	 * @return		void
	 */
	void Save()
	{
		std::string fileDir = "Resource Files\\Scenes\\";
	}
}