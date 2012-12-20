#include "..\..\..\Header Files\engine\scene\Scene.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	
	void Scene::ParseAndExecuteScript(std::string argScript)
	{
		std::vector<std::string> parts = explode(' ', argScript);
		std::string funcName = parts.at(0);

		if(funcName == "followPos")
		{
			Model* pModelTarget	= this->models[parts.at(1)];

			Vector3 posTarget = pModelTarget->GetPosition();
			Vector3 posCamera = this->pCamera->GetPosition();

			posCamera.x = posTarget.x;
			posCamera.y = posTarget.y + 2.0f;
			posCamera.z = posTarget.z - 10.0f;

			this->pCamera->SetPosition(posCamera);
		}
		else if(funcName == "followPosRot")
		{
			Model* pModelTarget	= this->models[parts.at(1)];
			
			Vector3 rotTarget = pModelTarget->GetRotation();
			Vector3 posTarget = pModelTarget->GetPosition();
			Vector3 rotCamera = this->pCamera->GetRotation();
			Vector3 posCamera = this->pCamera->GetPosition();

			rotCamera.x = rotTarget.x;
			rotCamera.y = rotTarget.y + D3DX_PI;
			rotCamera.z = rotTarget.z;

			posCamera.x = posTarget.x - (sin(rotCamera.y) * 10);
			posCamera.y = posTarget.y + 2;
			posCamera.z = posTarget.z - (cos(rotCamera.y) * 10);
			
			this->pCamera->SetRotation(rotCamera);
			this->pCamera->SetPosition(posCamera);
		}
	}

	//---Public methods---

	/**
	 * Constructs the Scene object, initialising the Window and Entity collection.
	 */
	Scene::Scene()
	{
		this->windows = std::list<Window*>();

		this->pCamera = new Camera();
		this->models = std::map<std::string, Model*>();
		this->scripts = std::list<std::string>();
	}

	/**
	 * Destructs the Scene object.
	 */
	Scene::~Scene()
	{
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing this object.
	 * @return		void
	 */
	void Scene::CleanUp()
	{
	}

	/**
	 * Update each entity in the models collection.
	 * @return		void
	 */
	void Scene::Update()
	{
		this->pCamera->Update();

		std::map<std::string, Model*>::iterator it;
		for(it = this->models.begin(); it != this->models.end(); it++)
		{
			it->second->Update();
		}

		for each(std::string script in this->scripts)
		{
			this->ParseAndExecuteScript(script);
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

		std::map<std::string, Model*>::iterator it;
		for(it = this->models.begin(); it != this->models.end(); it++)
		{
			argPRenderer->Push();
			it->second->Draw(argPRenderer);
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
		Logger::Log("Adding window to scene", Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
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
	 * Gets a model by name
	 * @param		std::string							The name of the model to return
	 * @return		Model*
	 */
	Model* Scene::GetModel(std::string argModelName)
	{
		return this->models[argModelName];
	}

	/**
	 * Obtain all the model pointers in the models collection.
	 * @return		std::map<std::string, Model*>		The entire model collection.
	 */
	std::map<std::string, Model*> Scene::GetModels()
	{
		return this->models;
	}

	/**
	 * Add an model pointer to the list of models.
	 * @param		std::string							The key index for the model
	 * @param		model								The model pointer to add to the collection of models.
	 * @return		void
	 */
	void Scene::AddModel(std::string argModelName, Model* argPModel)
	{
		this->models[argModelName] = argPModel;
	}

	/**
	 * Remove an model pointer from the collection of models.
	 * @param		std::string							The model name to remove from the collection of models.
	 * @return		void
	 */
	void Scene::RemoveModel(std::string argModelName)
	{
		this->models.erase(argModelName);
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