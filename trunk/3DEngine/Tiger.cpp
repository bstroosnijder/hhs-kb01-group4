#include "Tiger.h"

namespace engine
{
	Tiger::Tiger()
	{
	}

	Tiger::~Tiger()
	{
		this->CleanUp();
	}

	void Tiger::CleanUp()
	{
	}
	
	void Tiger::Load(ResourceManager* argPResourceManager, Renderer* argPRenderer)
	{
		this->SetResource(argPResourceManager->LoadResource(argPRenderer, "tiger.x"));
		Entity::Load(argPResourceManager, argPRenderer);
	}

	void Tiger::Update()
	{
		Entity::Update();
	}

	void Tiger::Draw(Renderer* argPRenderer)
	{
		DirectX9Renderer* pRenderer = (DirectX9Renderer*)argPRenderer;
		

		// Scaling
		D3DXMATRIXA16 matScaling;
		D3DXMatrixScaling(&matScaling, this->scaling.x, this->scaling.y, this->scaling.z);
		pRenderer->AddToWorldMatrix(&matScaling);

		// Position
		D3DXMATRIXA16 matPosition;
		D3DXMatrixTranslation(&matPosition, this->position.x, this->position.y, this->position.z);
		pRenderer->AddToWorldMatrix(&matPosition);
		
		// Rotation X
		D3DXMATRIXA16 matRotationX;
		D3DXMatrixRotationX(&matRotationX, this->rotation.x);
		pRenderer->AddToWorldMatrix(&matRotationX);
		// Rotation Y
		D3DXMATRIXA16 matRotationY;
		D3DXMatrixRotationY(&matRotationY, this->rotation.y);
		pRenderer->AddToWorldMatrix(&matRotationY);
		// Rotation Z
		D3DXMATRIXA16 matRotationZ;
		D3DXMatrixRotationZ(&matRotationZ, this->rotation.z);
		pRenderer->AddToWorldMatrix(&matRotationZ);


		// Call the parent draw to make sure the image is actually drawed
		Entity::Draw(argPRenderer);
	}
}