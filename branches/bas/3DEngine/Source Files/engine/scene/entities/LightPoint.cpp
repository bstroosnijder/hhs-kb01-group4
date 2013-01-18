#include "..\..\..\..\Header Files\engine\scene\entities\LightPoint.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Construct the Light Point object.
	 * @param		unsigned long		The index of the light
	 */
	LightPoint::LightPoint(unsigned long argIndex) : Entity()
	{
		Logger::Log("LightPoint: Initializing", Logger::INFO, __FILE__, __LINE__);
		
		this->index			= argIndex;
		this->enabled		= true;

		ZeroMemory(&this->light, sizeof(this->light));
		this->light.Type	= D3DLIGHT_POINT;

		this->range			= 100.0f;
		this->color			= D3DCOLOR_RGBA(255, 255, 255, 255);

		Logger::Log("LightPoint: Finished", Logger::INFO, __FILE__, __LINE__);
	}

	/**
	 * Destructs the Light Point object.
	 */
	LightPoint::~LightPoint()
	{
		Logger::Log("LightPoint: Disposing", Logger::INFO, __FILE__, __LINE__);
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void LightPoint::CleanUp()
	{
	}

	/**
	 * Default implementation of the Update method for all entities
	 * @return		void
	 */
	void LightPoint::Update()
	{
		Entity::Update();
	}

	/**
	 * Draw the model
	 * @param		Renderer*			The renderer to use.
	 * @return		void
	 */
	void LightPoint::Draw(Renderer* argPRenderer)
	{
		Entity::Draw(argPRenderer);
		// Apply the matrix transformations
		argPRenderer->TransformWorldMatrix();
		argPRenderer->TransformViewMatrix();
		argPRenderer->TransformProjectionMatrix();

		D3DXVECTOR3 vecScale;
		D3DXQUATERNION quadRotation;
		D3DXVECTOR3 vecPosition;
		D3DXMatrixDecompose(&vecScale, &quadRotation, &vecPosition, (D3DXMATRIXA16*)argPRenderer->GetWorldTop());

		this->light.Diffuse			= this->color;
		this->light.Position		= vecPosition;
		this->light.Range			= this->range;
		this->light.Attenuation0	= 0.0f;
		this->light.Attenuation1	= 0.125f;
		this->light.Attenuation2	= 0.0f;
		
		argPRenderer->SetLight(this->index, &light);
		argPRenderer->LightEnable(this->index, this->enabled);
	}

	/**
	 * Sets the light index
	 * @param		unsigned long		The index of the light
	 * @return		void
	 */
	void LightPoint::SetIndex(unsigned long argIndex)
	{
		this->index = argIndex;
	}

	/**
	 * Gets the light index
	 * @return		unsigned long
	 */
	unsigned long LightPoint::GetIndex()
	{
		return this->index;
	}

	/**
	 * Sets the range for the light point
	 * @param		float				The range of the light
	 * @return		void
	 */
	void LightPoint::SetRange(float argRange)
	{
		this->range = argRange;
	}

	/**
	 * Gets the range of the light point
	 * @return		float
	 */
	float LightPoint::GetRange()
	{
		return this->range;
	}

	/**
	 * Sets the color of the light
	 * @param		float				The Red color value
	 * @param		float				The Green color value
	 * @param		float				The Blue color value
	 * @param		float				The Alpha color value
	 * @return		void
	 */
	void LightPoint::SetColor(float argColorR, float argColorG, float argColorB, float argColorA)
	{
		this->color = D3DXCOLOR((argColorR / 255), (argColorG / 255), (argColorB / 255), (argColorA / 255));
	}
}