#include "..\..\..\Header Files\engine\scene\Scene.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Constructs the Scene object, initialising the Window and Entity collection.
	 */
	Scene::Scene()
	{
		this->windows = std::list<Window*>();

		this->pCamera = new Camera();
		this->models = std::map<std::string, Model*>();
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

	Camera* Scene::GetCamera()
	{
		return this->pCamera;
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
	 * Obtain all the model pointers in the models collection.
	 * @return		std::map<std::string, Model*>		The entire model collection.
	 */
	std::map<std::string, Model*> Scene::GetModels()
	{
		return this->models;
	}
}