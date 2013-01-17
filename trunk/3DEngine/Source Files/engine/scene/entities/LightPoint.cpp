#include "..\..\..\..\Header Files\engine\scene\entities\LightPoint.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Construct the Light Point object.
	 */
	LightPoint::LightPoint()
	{
		Logger::Log("LightPoint: Initializing", Logger::INFO, __FILE__, __LINE__);
		this->range = 100.0f;
		this->AddScript("doOrbitAtPlace y CW 0.007 56");
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
	 * @param		Renderer*		The renderer to use.
	 * @return		void
	 */
	void LightPoint::Draw(Renderer* argPRenderer)
	{
		Entity::Draw(argPRenderer);

		D3DXVECTOR3 vecScale;
		D3DXQUATERNION quadRotation;
		D3DXVECTOR3 vecPosition;
		D3DXMatrixDecompose(&vecScale, &quadRotation, &vecPosition, (D3DXMATRIXA16*)argPRenderer->GetWorldTop());

		D3DLIGHT9 light;
		ZeroMemory(&light, sizeof(light));
		light.Type			= D3DLIGHT_POINT;
		light.Diffuse		= this->color;
		light.Position		= D3DXVECTOR3(vecPosition.x, vecPosition.y, vecPosition.z);
		light.Range			= this->range;
		light.Attenuation0	= 0.0f;
		light.Attenuation1	= 0.125f;
		light.Attenuation2	= 0.0f;
		argPRenderer->SetLight(1, &light);
		argPRenderer->LightEnable(1, true);
	}

	/**
	 * Sets the range for the light point
	 * @param		float			The range of the light
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
	 * @param		float			The Red color value
	 * @param		float			The Green color value
	 * @param		float			The Blue color value
	 * @param		float			The Alpha color value
	 * @return		void
	 */
	void LightPoint::SetColor(float argColorR, float argColorG, float argColorB, float argColorA)
	{
		this->color = D3DXCOLOR((argColorR / 255), (argColorG / 255), (argColorB / 255), (argColorA / 255));
	}
}