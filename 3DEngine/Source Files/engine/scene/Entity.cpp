#include "..\..\..\Header Files\engine\scene\Entity.h"

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
	void Entity::ParseAndExecuteScript(std::string argScript)
	{
		std::vector<std::string> parts = explode(' ', argScript);
		std::string funcName = parts.at(0);

		if(funcName == "doOrbitAtPlace")
		{
			float speed		= 1;
			if(parts.at(1) == "CCW")
				speed		= -1;
			float rotSpeed	= (float)std::atof(parts.at(2).c_str());
			float radius	= (float)std::atof(parts.at(3).c_str());

			this->rotation.y += (rotSpeed * speed);
			this->position.x = ((sin(this->rotation.y + (D3DX_PI / 2)) * radius) * speed);
			this->position.z = ((cos(this->rotation.y + (D3DX_PI / 2)) * radius) * speed);
		}
		else
		{
			unsigned long posDot		= argScript.find(".");
			std::string vectorName		= argScript.substr(0, posDot);
			std::string vectorDirection	= argScript.substr((posDot + 1), 1);
			std::string amount			= argScript.substr((posDot + 2), 2);
			std::string value			= argScript.substr((posDot + 4));

			Vector3* vector;
			if(vectorName == "position")
				vector = &this->position;
			else if(vectorName == "rotation")
				vector = &this->rotation;
			else if(vectorName == "scaling")
				vector = &this->scaling;

			float* direction;
			if(vectorDirection == "x")
				direction = &vector->x;
			else if(vectorDirection == "y")
				direction = &vector->y;
			else if(vectorDirection == "z")
				direction = &vector->z;

			if(amount == "++")
				(*direction)++;
			else if(amount == "--")
				(*direction)--;
			else if(amount == "+=")
				(*direction) += (float)std::atof(value.c_str());
			else if(amount == "-=")
				(*direction) -= (float)std::atof(value.c_str());
		}
	}

	//---Public methods---

	/**
	 * Constructs the Scene object, initialising the Window and Entity collection.
	 */
	Entity::Entity()
	{
		Logger::Log("Entity: Initializing", Logger::INFO, __FILE__, __LINE__);

		this->SetScaling(Vector3(1.0f, 1.0f, 1.0f));
		this->scripts = std::list<std::string>();

		Logger::Log("Entity: Finished", Logger::INFO, __FILE__, __LINE__);
	}

	/**
	 * Destructs the Scene object.
	 */
	Entity::~Entity()
	{
		Logger::Log("Entity: Disposing", Logger::INFO, __FILE__, __LINE__);
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing this object.
	 * @return		void
	 */
	void Entity::CleanUp()
	{
	}

	/**
	 * Default implementation of the Update method for all entities
	 * @return		void
	 */
	void Entity::Update()
	{
		std::list<std::string>::iterator scriptIt;
		for (scriptIt = this->scripts.begin(); scriptIt != this->scripts.end(); scriptIt++)
		{
			this->ParseAndExecuteScript(*scriptIt);
		}
	}

	/**
	 * Default implementation of the Draw method for all entities
	 * @param		Renderer*				The renderer to use.
	 * @return		void
	 */
	void Entity::Draw(Renderer* argPRenderer)
	{
		D3DXMatrixIdentity(&this->matWorld);

		// Scaling
		D3DXMATRIXA16 matScaling;
		D3DXMatrixScaling(&matScaling, this->scaling.x, this->scaling.y, this->scaling.z);
		D3DXMatrixMultiply(&this->matWorld, &this->matWorld, &matScaling);
		
		// Rotation X
		D3DXMATRIXA16 matRotationX;
		D3DXMatrixRotationX(&matRotationX, this->rotation.x);
		D3DXMatrixMultiply(&this->matWorld, &this->matWorld, &matRotationX);
		// Rotation Y
		D3DXMATRIXA16 matRotationY;
		D3DXMatrixRotationY(&matRotationY, this->rotation.y);
		D3DXMatrixMultiply(&this->matWorld, &this->matWorld, &matRotationY);
		// Rotation Z
		D3DXMATRIXA16 matRotationZ;
		D3DXMatrixRotationZ(&matRotationZ, this->rotation.z);
		D3DXMatrixMultiply(&this->matWorld, &this->matWorld, &matRotationZ);

		// Position
		D3DXMATRIXA16 matPosition;
		D3DXMatrixTranslation(&matPosition, this->position.x, this->position.y, this->position.z);
		D3DXMatrixMultiply(&this->matWorld, &this->matWorld, &matPosition);

		// Multiplies the entity world matrix with the renderer's world matrix (this->matWorld * renderer->matWorld)
		argPRenderer->AddToWorldMatrix(&this->matWorld);

		// Apply the matrix transformations
		argPRenderer->TransformWorldMatrix();
		argPRenderer->TransformViewMatrix();
		argPRenderer->TransformProjectionMatrix();
	}

	/**
	 * Setter for the position
	 * @param		Vector3					The new position for the entity
	 * @return		void
	 */
	void Entity::SetPosition(Vector3 argPosition)
	{
		this->position = argPosition;
	}

	/**
	 * Setter for the rotation
	 * @param		Vector3					The new rotation for the entity
	 * @return		void
	 */
	void Entity::SetRotation(Vector3 argRotation)
	{
		this->rotation = argRotation;
	}

	/**
	 * Setter for the scaling
	 * @param		Vector3					The new scaling for the entity
	 * @return		void
	 */
	void Entity::SetScaling(Vector3 argScaling)
	{
		this->scaling = argScaling;
	}

	/**
	 * Getter for the position
	 * @return		Vector3					The position of the entity
	 */
	Vector3 Entity::GetPosition()
	{
		return this->position;
	}
	
	/**
	 * Getter for the rotation
	 * @return		Vector3					The rotation of the entity
	 */
	Vector3 Entity::GetRotation()
	{
		return this->rotation;
	}
	
	/**
	 * Getter for the rotation
	 * @return		Vector3					The scaling of the entity
	 */
	Vector3 Entity::GetScaling()
	{
		return this->scaling;
	}
	
	/**
	 * Adds a script to the entity to be executed during the update
	 * @param		std::string				The script to add
	 * @return		void
	 */
	void Entity::AddScript(std::string argScript)
	{
		this->scripts.push_back(argScript);
	}
}