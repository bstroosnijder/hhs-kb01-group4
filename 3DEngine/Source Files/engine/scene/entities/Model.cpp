#include "..\..\..\..\Header Files\engine\scene\entities\Model.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	
	/**
	 * A method that performs the action corresponding to the bind
	 * @param		std::string		The bind to do
	 * @return		void
	 */
	void Model::DoBind(std::string argBind, long argSpeed)
	{
		float speed = argSpeed * 0.025f;

		// Move Forward
		if(argBind == "move_forward")
		{
			this->position.x -= sin(this->rotation.y);
			//this->position.y += sin(this->rotation.x);
			this->position.z -= cos(this->rotation.y);
		}
		// Move Backward
		else if(argBind == "move_backward")
		{
			this->position.x += sin(this->rotation.y);
			//this->position.y -= sin(this->rotation.x);
			this->position.z += cos(this->rotation.y);
		}
		// Move Left
		else if(argBind == "move_left")
		{
			this->position.x -= sin(this->rotation.y - (D3DX_PI / 2));
			//this->position.y += sin(this->rotation.x);
			this->position.z -= cos(this->rotation.y - (D3DX_PI / 2));
		}
		// Move Right
		else if(argBind == "move_right")
		{
			this->position.x += sin(this->rotation.y - (D3DX_PI / 2));
			//this->position.y -= sin(this->rotation.x);
			this->position.z += cos(this->rotation.y - (D3DX_PI / 2));
		}
		// Move Up
		else if(argBind == "move_up")
		{
			this->position.y += speed * 100;
		}
		// Move Down
		else if(argBind == "move_down")
		{
			this->position.y -= speed * 100;
		}
		// Turn Left
		else if(argBind == "turn_left")
		{
			this->rotation.y -= speed;
		}
		// Turn Right
		else if(argBind == "turn_right")
		{
			this->rotation.y += speed;
		}
		// Pan Up
		else if(argBind == "pan_up")
		{
			this->rotation.x -= speed;
		}
		// Pan Down
		else if(argBind == "pan_down")
		{
			this->rotation.x += speed;
		}

		// Reset
		else if(argBind == "reset")
		{
			this->position = Vector3(0.0f, 0.0f, 0.0f);
			this->rotation = Vector3(0.0f, 0.0f, 0.0f);
			this->scaling  = Vector3(1.0f, 1.0f, 1.0f);
		}
	}

	//---Public methods---

	/**
	 * Constructs the Scene object, initialising the Window and Entity collection.
	 */
	Model::Model(Resource* argPResource) : Entity()
	{
		this->pResource = argPResource;
		this->models = std::map<std::string, Model*>();
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
	 * Handle any incomming keyboard events
	 * @param		std::map<std::string, std::string>		The bindings and keys
	 * @param		KeyboardState*							The state of the keyboard
	 * @return		void
	 */
	void Model::DoKeyboardEvent(std::map<std::string, std::string> argBinds, KeyboardState* argPState)
	{
		std::map<std::string, std::string>::iterator bindsIt;
		for(bindsIt = argBinds.begin(); bindsIt != argBinds.end(); bindsIt++)
		{
			std::string key		= bindsIt->first;
			std::string bind	= bindsIt->second;

			if(argPState->IsBindActive(key))
			{
				long speed = 1;
				this->DoBind(bind, speed);
			}
		}
	}
	
	/**
	 * Handle any incomming mouse events
	 * @param		std::map<std::string, std::string>		The bindings and keys
	 * @param		MouseState*								The state of the mouse
	 * @return		void
	 */
	void Model::DoMouseEvent(std::map<std::string, std::string> argBinds, MouseState* argPState)
	{
		std::map<std::string, std::string>::iterator bindsIt;
		for(bindsIt = argBinds.begin(); bindsIt != argBinds.end(); bindsIt++)
		{
			std::string key		= bindsIt->first;
			std::string bind	= bindsIt->second;

			if(argPState->IsBindActive(key))
			{
				long speed = (argPState->GetMouseSpeed(key) / 10.5);
				if(speed <=0)
				{
					speed = 1;
				}
				this->DoBind(bind, speed);
			}
		}
	}
	
	/**
	 * Handle any incomming joystick events
	 * @param		std::map<std::string, std::string>		The bindings and keys
	 * @param		KeyboardState*							The state of the joystick
	 * @return		void
	 */
	void Model::DoJoyStickEvent(std::map<std::string, std::string> argBinds, JoyStickState* argPState)
	{
		std::map<std::string, std::string>::iterator bindsIt;
		for(bindsIt = argBinds.begin(); bindsIt != argBinds.end(); bindsIt++)
		{
			std::string key		= bindsIt->first;
			std::string bind	= bindsIt->second;

			if(argPState->IsBindActive(key))
			{
				float speed = (argPState->GetStickSpeed(key) / 10.5);
				this->DoBind(bind, speed);
			}
		}
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