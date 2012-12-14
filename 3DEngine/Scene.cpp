#include "Scene.h"

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
		this->models = std::list<Model*>();
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
	 * Loads the scene and all of it's models
	 * @return		void
	 */
	void Scene::Load(ResourceManager* argPResourceManager, Renderer* argPRenderer)
	{
		for each(Model* pModel in this->models)
		{
			pModel->Load(argPResourceManager, argPRenderer);
		}
	}

	/**
	 * Update each entity in the models collection.
	 * @return		void
	 */
	void Scene::Update()
	{
		this->pCamera->Update();
		for each(Model* pModel in this->models)
		{
			pModel->Update();
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
		for each(Model* pModel in this->models)
		{
			argPRenderer->Push();
			pModel->Draw(argPRenderer);
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
	 * @param		model						The model pointer to add to the collection of models.
	 * @return		void
	 */
	void Scene::AddModel(Model* argPModel)
	{
		this->models.push_back(argPModel);
	}

	/**
	 * Remove an model pointer from the collection of models.
	 * @param		Model*						The model pointer to remove from the collection of models.
	 * @return		void
	 */
	void Scene::RemoveModel(Model* argPModel)
	{
		this->models.remove(argPModel);
	}

	/**
	 * Obtain all the model pointers in the models collection.
	 * @return		std::list<Model*>			The entire model collection.
	 */
	std::list<Model*> Scene::GetModels()
	{
		return this->models;
	}
}