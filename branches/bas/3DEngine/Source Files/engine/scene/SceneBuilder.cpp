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
		if(argBind == "do_command")
		{
			// The line buffer used to read lines from the file
			char cLine[256];
			// exploded line data
			std::vector<std::string> data;

			Logger::Log("SceneBuilder: Starting command parser\nEnter Command:", Logger::INFO, __FILE__, __LINE__);

			// Reads the command line
			std::cin.getline(cLine, sizeof(cLine));
			// explodes the data
			data = explode(' ', std::string(cLine));

			// Check the command
			std::string command	= data.at(0);

			// Spawn a entity / model / light
			if(command == "spawn")
			{
				// Name of the entity
				std::string name	= data.at(1);
				// What is the type of entity
				std::string type	= data.at(2);
				// The entity we are going to add
				Entity* pEntity;

				Vector3 cPos		= this->pScene->GetCamera()->GetPosition();
				Vector3 cRot		= this->pScene->GetCamera()->GetRotation();
				Vector3 cScale		= this->pScene->GetCamera()->GetScaling();

				if(type == "model")
				{
					Logger::Log("SceneBuilder: Spawning a model", Logger::WARNING, __FILE__, __LINE__);
					// Get the mesh file and load it
					std::string mMesh	= data.at(12);
					this->pResourceManager->LoadMesh(this->pRenderer, mMesh);
					// Create a new model
					pEntity			= new Model(this->pResourceManager->NewResource(mMesh));

					pEntity->SetPosition(Vector3(	this->FloatIfStringDefault(data.at(3), cPos.x),
													this->FloatIfStringDefault(data.at(4), cPos.y),
													this->FloatIfStringDefault(data.at(5), cPos.z)));
					pEntity->SetRotation(Vector3(	this->FloatIfStringDefault(data.at(6), cRot.x),
													this->FloatIfStringDefault(data.at(7), cRot.y),
													this->FloatIfStringDefault(data.at(8), cRot.z)));
					pEntity->SetScaling(Vector3(	this->FloatIfStringDefault(data.at(9), cScale.x),
													this->FloatIfStringDefault(data.at(10), cScale.y),
													this->FloatIfStringDefault(data.at(11), cScale.z)));
					unsigned long iTex	= 13;
					for(unsigned long i = iTex; i < data.size(); i++)
					{
						std::string mTexture = data.at(i);
						this->pResourceManager->LoadTexture(this->pRenderer, mTexture);

						((Model*)pEntity)->SetTexture((i - iTex), this->pResourceManager->GetTexture(mTexture));
					}
				}
				else if(type == "light")
				{
					Logger::Log("SceneBuilder: Spawning a light", Logger::INFO, __FILE__, __LINE__);
					// Create a new light
					pEntity				= new LightPoint(this->pRenderer->GetNextLightIndex());
					float lRange		= (float)std::atof(data.at(6).c_str());
					float lColorR		= (float)std::atof(data.at(7).c_str());
					float lColorG		= (float)std::atof(data.at(8).c_str());
					float lColorB		= (float)std::atof(data.at(9).c_str());
					float lColorA		= (float)std::atof(data.at(10).c_str());
					

					pEntity->SetPosition(Vector3(	this->FloatIfStringDefault(data.at(3), cPos.x),
													this->FloatIfStringDefault(data.at(4), cPos.y),
													this->FloatIfStringDefault(data.at(5), cPos.z)));
					pEntity->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
					pEntity->SetScaling(Vector3(1.0f, 1.0f, 1.0f));
					((LightPoint*)pEntity)->SetRange(lRange);
					((LightPoint*)pEntity)->SetColor(lColorR, lColorG, lColorB, lColorA);
				}
				else
				{
					Logger::Log("SceneBuilder: Unsupported entity type: " + type, Logger::WARNING, __FILE__, __LINE__);
				}

				this->pScene->AddEntity(name, pEntity);
			}
			// Load skybox / heightmap
			else if(command == "load")
			{
				// What is the type what we load
				std::string type	= data.at(1);

				if(type == "skybox")
				{
					Logger::Log("SceneBuilder: Loading a skybox", Logger::INFO, __FILE__, __LINE__);

					std::string skyTexture	= data.at(2);
					unsigned long skySize	= (unsigned long)std::atof(data.at(3).c_str());
					this->pResourceManager->LoadTexture(this->pRenderer, skyTexture);

					Skybox* pSkybox = new Skybox();
					pSkybox->SetupVertices(this->pRenderer, skySize);
					pSkybox->SetTexture(0, this->pResourceManager->GetTexture(skyTexture));
					this->pScene->SetSkybox(pSkybox);
				}
				else if(type == "heightmap")
				{
					Logger::Log("SceneBuilder: Loading a heightmap", Logger::INFO, __FILE__, __LINE__);

					std::string mapFileName				= data.at(2);
					float pixelScale					= (float)std::atof(data.at(3).c_str());
					unsigned long smoothingIterations	= (unsigned long)std::atof(data.at(4).c_str());

					Heightmap* pHeightmap = new Heightmap();
					this->pScene->SetHeightmap(pHeightmap);
					pHeightmap->SetupVertices(this->pRenderer, mapFileName, pixelScale, smoothingIterations);

					unsigned long iTex = 5;
					for(unsigned long i = iTex; i < data.size(); i++)
					{
						std::string mapTexture = data.at(i);
						this->pResourceManager->LoadTexture(this->pRenderer, mapTexture);

						pHeightmap->SetTexture((i - iTex), this->pResourceManager->GetTexture(mapTexture));
					}
				}
				else
				{
					Logger::Log("SceneBuilder: Unsupported load type: " + type, Logger::WARNING, __FILE__, __LINE__);
				}
			}
			// Save the heightmap and write to a file
			else if(command == "save")
			{
				// Set the dir to save to
				std::string fileDir	= "Resource Files\\Scenes\\";
				// Set the file extension
				std::string fileExt	= ".scene";
				// Create the output stream
				std::ofstream out	= std::ofstream(fileDir + this->fileName + fileExt);
				
				// === SEGMENT: Camera ===
				Camera* pCamera	= this->pScene->GetCamera();
				out << "#camera" << std::endl;

				Vector3 cPos	= pCamera->GetPosition();
				out << cPos.x << ";" << cPos.y << ";" << cPos.z << ";";
				Vector3 cRot	= pCamera->GetRotation();
				out << cRot.x << ";" << cRot.y << ";" << cRot.z << ";";
				Vector3 cScale	= pCamera->GetScaling();
				out << cScale.x << ";" << cScale.y << ";" << cScale.z << std::endl;
				


				// Close and save the output stream
				out.close();
			}
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