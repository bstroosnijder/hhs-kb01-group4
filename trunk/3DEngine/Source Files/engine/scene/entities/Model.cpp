#include "..\..\..\..\Header Files\engine\scene\entities\Model.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Constructs the Scene object, initialising the Window and Entity collection.
	 */
	Model::Model(Resource* argPResource) : Entity()
	{
		Logger::Log("Model: Initializing", Logger::INFO, __FILE__, __LINE__);
		this->pResource = argPResource;
		this->models = std::map<std::string, Model*>();
		Logger::Log("Model: Finished", Logger::INFO, __FILE__, __LINE__);
	}
	
	/**
	 * Destructs the Scene object.
	 */
	Model::~Model()
	{
		Logger::Log("Model: Disposing", Logger::INFO, __FILE__, __LINE__);
		this->CleanUp();
	}
	
	/**
	 * Lazy cleanup method for destructing this object.
	 * @return		void
	 */
	void Model::CleanUp()
	{
	}

	/**
	 * Default implementation of the Update method for all entities
	 * @return		void
	 */
	void Model::Update()
	{
		Entity::Update();
		
		std::map<std::string, Model*>::iterator it;
		for(it = this->models.begin(); it != this->models.end(); it++)
		{
			Model* pModel = it->second;
			pModel->Update();
		}
	}

	/**
	 * Draw the model
	 * @param		Renderer*				The renderer to use.
	 * @return		void
	 */
	void Model::Draw(Renderer* argPRenderer)
	{
		Entity::Draw(argPRenderer);

		// Get the mesh
		LPD3DXMESH mesh = this->pResource->pMesh->mesh;
		D3DMATERIAL9* pMeshMaterials = this->pResource->pMesh->materials;
		LPDIRECT3DTEXTURE9* pMeshTextures = this->pResource->textures;

		for(unsigned long i = 0; i < this->pResource->pMesh->numMaterials; i++)
		{
			argPRenderer->SetMaterial(&pMeshMaterials[i]);
			argPRenderer->SetTexture(0, pMeshTextures[i]);
			mesh->DrawSubset(i);
		}
		
		std::map<std::string, Model*>::iterator it;
		for(it = this->models.begin(); it != this->models.end(); it++)
		{
			argPRenderer->Push();
			it->second->Draw(argPRenderer);
			argPRenderer->Pop();
		}
	}

	/**
	 * Processes any input events
	 * @param		std::string		the bind to execute
	 * @param		float			the speed
	 * @return		void
	 */
	void Model::InputEvent(std::string argBind, float argSpeed)
	{
		// Move Forward
		if(argBind == "move_forward")
		{
			this->position.x -= (sin(this->rotation.y) * argSpeed);
			//this->position.y += (sin(this->rotation.x) * argSpeed);
			this->position.z -= (cos(this->rotation.y) * argSpeed);
		}
		// Move Backward
		else if(argBind == "move_backward")
		{
			this->position.x += (sin(this->rotation.y) * argSpeed);
			//this->position.y -= (sin(this->rotation.x) * argSpeed);
			this->position.z += (cos(this->rotation.y) * argSpeed);
		}
		// Move Forward or Backward
		else if(argBind == "move_forward_backward")
		{
			this->position.x += (sin(this->rotation.y) * argSpeed);
			//this->position.y -= (sin(this->rotation.x) * argSpeed);
			this->position.z += (cos(this->rotation.y) * argSpeed);
		}
		// Move Left
		else if(argBind == "move_left")
		{
			this->position.x -= (sin(this->rotation.y - (D3DX_PI / 2)) * argSpeed);
			//this->position.y += (sin(this->rotation.x) * argSpeed);
			this->position.z -= (cos(this->rotation.y - (D3DX_PI / 2)) * argSpeed);
		}
		// Move Right
		else if(argBind == "move_right")
		{
			this->position.x += (sin(this->rotation.y - (D3DX_PI / 2)) * argSpeed);
			//this->position.y -= (sin(this->rotation.x) * argSpeed);
			this->position.z += (cos(this->rotation.y - (D3DX_PI / 2)) * argSpeed);
		}
		// Move Left or Right
		else if(argBind == "move_left_right")
		{
			this->position.x += (sin(this->rotation.y - (D3DX_PI / 2)) * argSpeed);
			//this->position.y -= (sin(this->rotation.x) * argSpeed);
			this->position.z += (cos(this->rotation.y - (D3DX_PI / 2)) * argSpeed);
		}
		// Move Up
		else if(argBind == "move_up")
		{
			this->position.y += argSpeed;
		}
		// Move Down
		else if(argBind == "move_down")
		{
			this->position.y -= argSpeed;
		}
		// Turn Left
		else if(argBind == "turn_left")
		{
			this->rotation.y = (float)(argSpeed / 10);
		}
		// Turn Right
		else if(argBind == "turn_right")
		{
			this->rotation.y = (float)(argSpeed / 10);
		}
		// Turn Left or Right
		else if(argBind == "turn_left_right")
		{
			this->rotation.y += (float)(argSpeed / 10);
		}
		// Pan Up
		else if(argBind == "pan_up")
		{
			this->rotation.x -= (float)(argSpeed / 10);
		}
		// Pan Down
		else if(argBind == "pan_down")
		{
			this->rotation.x += (float)(argSpeed / 10);
		}
		// Pan Up or Down
		else if(argBind == "pan_up_down")
		{
			this->rotation.x -= (float)(argSpeed / 10);
		}

		// Reset
		else if(argBind == "reset")
		{
			this->position = Vector3(0.0f, 0.0f, 0.0f);
			this->rotation = Vector3(0.0f, 0.0f, 0.0f);
			this->scaling  = Vector3(1.0f, 1.0f, 1.0f);
		}
	}

	/**
	 * Setter for the resource
	 * @param		Resource*				The new resource for the model
	 * @return		void
	 */
	void Model::SetResource(Resource* argPResource)
	{
		this->pResource = argPResource;
	}
	
	/**
	 * Sets a custom texture at the givin index in the resource
	 * @param		unsigned long		The index to put the texture at
	 * @param		LPDIRECT3DTEXTURE9	The texture to add at the index
	 * @return		void
	 */
	void Model::SetTexture(unsigned long argIndex, LPDIRECT3DTEXTURE9 argTexture)
	{
		this->pResource->textures[argIndex] = argTexture;
	}

	/**
	 * Gets a model
	 * @param		std::string			The model name
	 * @param		Model*				The model
	 */
	Model* Model::GetModel(std::string argModelName)
	{
		return this->models[argModelName];
	}

	/**
	 * Adds a model
	 * @param		Model*					The model to add
	 * @param		std::string				The name of the model
	 * @return		void
	 */
	void Model::AddModel(std::string argModelName, Model* argPModel)
	{
		this->models[argModelName] = argPModel;
	}
}