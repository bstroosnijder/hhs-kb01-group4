#include "..\..\..\Header Files\engine\scene\Scene.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	
	/**
	 * The #scripts segment in the scene file is sent to this method for interpretation.
	 * Each line interpreted this way is executed and loaded directly.
	 * @param		std::string		The script which is to be parsed and executed.
	 * @return		void
	 */
	void Scene::ParseAndExecuteScript(std::string argScript)
	{
		std::vector<std::string> parts = explode(' ', argScript);
		std::string funcName = parts.at(0);

		// Makes the camera follow an entity only with it's position
		if(funcName == "followPos")
		{
			Entity* pModelTarget	= this->entities[parts.at(1)];

			Vector3 posTarget = pModelTarget->GetPosition();
			Vector3 posCamera = this->pCamera->GetPosition();

			posCamera.x = posTarget.x;
			posCamera.y = posTarget.y + 2.0f;
			posCamera.z = posTarget.z - 10.0f;

			this->pCamera->SetPosition(posCamera);
		}
		// Makes the camera follow an entity including it's rotation (as in a 3d person camera)
		else if(funcName == "followPosRot")
		{
			Entity* pModelTarget	= this->entities[parts.at(1)];
			if(pModelTarget == NULL)
				return;
			
			Vector3 rotTarget = pModelTarget->GetRotation();
			Vector3 posTarget = pModelTarget->GetPosition();
			Vector3 rotCamera = this->pCamera->GetRotation();
			Vector3 posCamera = this->pCamera->GetPosition();

			rotCamera.x = (rotTarget.x * -1) - (D3DX_PI/2);
			rotCamera.y = rotTarget.y + D3DX_PI;
			rotCamera.z = rotTarget.z;

			posCamera.x = posTarget.x - (sin(rotCamera.y) * 10);
			posCamera.y = posTarget.y +2+ (tan(rotCamera.x) * 10);
			posCamera.z = posTarget.z - (cos(rotCamera.y) * 10);
			
			this->pCamera->SetRotation(rotCamera);
			this->pCamera->SetPosition(posCamera);
		}
		// makes a entity rotate left
		else if(funcName == "rotLeft")
		{
			Entity* pModelTarget	= this->entities[parts.at(1)];

			Vector3 posTarget = pModelTarget->GetRotation();

			posTarget.y -= 0.10f;

			pModelTarget->SetRotation(posTarget);
		}
		// makes a entity rotate right
		else if(funcName == "rotRight")
		{
			Entity* pModelTarget	= this->entities[parts.at(1)];

			Vector3 posTarget = pModelTarget->GetRotation();

			posTarget.y += 0.10f;

			pModelTarget->SetRotation(posTarget);
		}
	}

	//---Public methods---

	/**
	 * Constructs the Scene object, initialising the Window and Entity collection.
	 */
	Scene::Scene()
	{
		Logger::Log("Scene: Initializing", Logger::INFO, __FILE__, __LINE__);

		this->windows = std::list<Window*>();
		
		this->pCamera		= new Camera();
		this->pSkybox		= NULL;
		this->pHeightmap	= NULL;
		this->entities		= std::map<std::string, Entity*>();
		this->scripts		= std::list<std::string>();
		
		Logger::Log("Scene: Finished", Logger::INFO, __FILE__, __LINE__);
	}

	/**
	 * Destructs the Scene object.
	 */
	Scene::~Scene()
	{
		Logger::Log("Scene: Disposing", Logger::INFO, __FILE__, __LINE__);
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing this object.
	 * @return		void
	 */
	void Scene::CleanUp()
	{
		std::list<Window*>::iterator windowIt;
		for (windowIt = this->windows.begin(); windowIt != this->windows.end(); windowIt++)
		{
			delete *windowIt;
		}

		if(this->pCamera != NULL)
		{
			delete this->pCamera;
		}

		if(this->pSkybox != NULL)
		{
			delete this->pSkybox;
		}

		if(this->pHeightmap != NULL)
		{
			delete this->pHeightmap;
		}

		std::map<std::string, Entity*>::iterator entitiesIt;
		for(entitiesIt = this->entities.begin(); entitiesIt != this->entities.end(); entitiesIt++)
		{
			delete entitiesIt->second;
		}
		this->entities.clear();

		this->scripts.clear();
	}

	/**
	 * Update each entity in the models collection.
	 * @return		void
	 */
	void Scene::Update()
	{
		this->pCamera->Update();
		if(this->pSkybox != NULL)
		{
			this->pSkybox->Update();
		}
		if(this->pHeightmap != NULL)
		{
			this->pHeightmap->Update();
		}

		std::map<std::string, Entity*>::iterator entityIt;
		for(entityIt = this->entities.begin(); entityIt != this->entities.end(); entityIt++)
		{
			Entity* pEntity = entityIt->second;
			pEntity->Update();

			//Vector3 pos		= pEntity->GetPosition();
			//float lev		= 5.0f;
			//float height	= this->pHeightmap->GetHeight(pos.x, pos.z);

			//if((pos.y - lev) > height)
			//{
			//	pos.y -= 0.1f;
			//}
			//else
			//{
			//	pos.y = height + lev;
			//}

			//pEntity->SetPosition(pos);

		}

		std::list<std::string>::iterator scriptIt;
		for (scriptIt = this->scripts.begin(); scriptIt != this->scripts.end(); scriptIt++)
		{
			this->ParseAndExecuteScript(*scriptIt);
		}
	}

	/**
	 * Draw each entity in the entities collection.
	 * @param		Renderer*					argPRenderer is the current renderer to which the entity will draw
	 * @return		void
	 */
	void Scene::Draw(Renderer* argPRenderer)
	{
		argPRenderer->Push();
		this->pCamera->Draw(argPRenderer);
		if(this->pSkybox != NULL)
		{
			argPRenderer->Push();
			this->pSkybox->Draw(argPRenderer);
			argPRenderer->Pop();
		}
		if(this->pHeightmap != NULL)
		{
			this->pHeightmap->Draw(argPRenderer);
		}

		std::map<std::string, Entity*>::iterator entityIt;
		for(entityIt = this->entities.begin(); entityIt != this->entities.end(); entityIt++)
		{
			Entity* pEntity = entityIt->second;
			argPRenderer->Push();
			pEntity->Draw(argPRenderer);
			argPRenderer->Pop();
		}
		argPRenderer->Pop();
	}

	/**
	 * Adds a window to the window list of the scene. the scene will render in these windows
	 * @param		Window*						The window to add to the scene
	 * @return		void
	 */
	void Scene::AddWindow(Window* argPWindow)
	{
		Logger::Log("Adding window to scene", Logger::INFO, __FILE__, __LINE__);
		this->windows.push_back(argPWindow);
	}

	/**
	 * Removes a window from the window list of the scene
	 * @param		Window*						The window to remove
	 * @return		void
	 */
	void Scene::RemoveWindow(Window* argPWindow)
	{
		this->windows.remove(argPWindow);
	}

	/**
	 * Getter for the window list
	 * @return		std::list<Window*>			The list of windows
	 */
	std::list<Window*> Scene::GetWindows()
	{
		return this->windows;
	}

	/**
	 * Gets the camera object
	 * @return		Camera*
	 */
	Camera* Scene::GetCamera()
	{
		return this->pCamera;
	}

	/**
	 * Gets the skybox object
	 * @return		Skybox*
	 */
	Skybox* Scene::GetSkybox()
	{
		return this->pSkybox;
	}

	/**
	 * Sets the skybox object
	 * @param		Skybox*						The skybox to add
	 * @return		void
	 */
	void Scene::SetSkybox(Skybox* argPSkybox)
	{
		this->pSkybox = argPSkybox;
	}
	
	/**
	 * Gets the heightmap object
	 * @return		Heightmap*
	 */
	Heightmap* Scene::GetHeightmap()
	{
		return this->pHeightmap;
	}

	/**
	 * Sets the heightmap object
	 * @param		Heightmap*					The heightmap to add
	 * @return		void
	 */
	void Scene::SetHeightmap(Heightmap* argPHeightmap)
	{
		this->pHeightmap = argPHeightmap;
	}

	/**
	 * Gets a entity by name
	 * @param		std::string							The name of the entity to return
	 * @return		Entity*
	 */
	Entity* Scene::GetEntity(std::string argEntityName)
	{
		return this->entities[argEntityName];
	}

	/**
	 * Obtain all the entity pointers in the entities collection.
	 * @return		std::map<std::string, Entity*>		The entire entity collection.
	 */
	std::map<std::string, Entity*> Scene::GetEntities()
	{
		return this->entities;
	}

	/**
	 * Add an entity pointer to the list of entities.
	 * @param		std::string							The key index for the entity
	 * @param		Entity*								The entity pointer to add to the collection of entities.
	 * @return		void
	 */
	void Scene::AddEntity(std::string argEntityName, Entity* argPEntity)
	{
		this->entities[argEntityName] = argPEntity;
	}

	/**
	 * Remove an entity pointer from the collection of entities.
	 * @param		std::string							The entity name to remove from the collection of entities.
	 * @return		void
	 */
	void Scene::RemoveEntity(std::string argEntityName)
	{
		this->entities.erase(argEntityName);
	}

	/**
	 * Adds a script to the scene to be executed during the update
	 * @param		std::string				The script to add
	 * @return		void
	 */
	void Scene::AddScript(std::string argScript)
	{
		this->scripts.push_back(argScript);
	}
}